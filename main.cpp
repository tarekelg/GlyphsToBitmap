
#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>

using namespace std;

void PrintMonochromeBitmap(FT_GlyphSlot glyph){
  //Check if glyph is a bitmap
  if(glyph->format != FT_GLYPH_FORMAT_BITMAP){
    cout << "Glypg is not a bitmap!" << endl;
    return;
  }

  //Print bitmap details
  FT_Bitmap bitmap = glyph->bitmap;

  //Print bitmap dimension
  cout << "Bitmap Dimensions: \n" << "width: " << bitmap.width << "\nrows: " << bitmap.rows << "\npitch: " << bitmap.pitch <<  endl;

  for(int y = 0; y< bitmap.rows; ++y){
    for (int x = 0; x < bitmap.width; x++)
    {
      //Calculate byte and bit position
      int byte_index = x / 8;
      int bit_position = 7- (x%8);

      // Extract the bit
            int bit = (bitmap.buffer[y * bitmap.pitch + byte_index] >> bit_position) & 1;

            cout << bit;

    }
    cout << endl;
    
  }

}

int main(){

  FT_Library library;
  FT_Face       face;

  FT_GlyphSlot  slot;
  FT_Matrix     matrix;                 /* transformation matrix */
  FT_Vector     pen;                    /* untransformed origin  */
  FT_Error      error;
  int load_flags;

  cout << "Test" << endl;
  
  error= FT_Init_FreeType(&library);
  if(error){
    cerr << "FreeType initialization error" << endl;
    return 1;
  }

   // Correct font path
    const char* fontPath = "C:\\Windows\\Fonts\\arial.ttf";

error= FT_New_Face(library, fontPath,0,&face);

if(error==FT_Err_Unknown_File_Format){
  cout << "Unkown File format" << endl;
}else if(error){
  cout << "font file could not be opened" << endl;
}

if(!error){
   cout << "Number of glyphs: " << face->num_glyphs << endl;
   cout << "Face Size x_ppem=" << face->size->metrics.x_ppem << endl;    
    cout << "Face Size y_ppem=" << face->size->metrics.y_ppem << endl;  
}

//set size of the object top 16 pt
error= FT_Set_Char_Size(face,0,16*64,300,300);

if(!error){
   cout << "size was changed" << endl;
   cout << "Face Size x_ppem=" << face->size->metrics.x_ppem << endl;    
    cout << "Face Size y_ppem=" << face->size->metrics.y_ppem << endl;  
}

//set size of the object top 16 pixels

error=FT_Set_Pixel_Sizes(face, 0, 16);

if(!error){
   cout << "size was changed" << endl;
   cout << "Face Size x_ppem=" << face->size->metrics.x_ppem << endl;    
    cout << "Face Size y_ppem=" << face->size->metrics.y_ppem << endl;  
}

//Loading Glyph Image
//get Glyph index

 int glyph_index=FT_Get_Char_Index(face, 84);

 cout << glyph_index << endl;

 error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);


 
if(!error){
   cout << "glyph was loaded" << endl;
   cout << face->glyph->format << endl;
}else if (error ==6)
{
  cerr << "Invalid Argument" << endl;

}

//convert to bitmap

error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_MONO);


if(!error){
   cout << "glyph was rendered into bitmap" << endl;
  
}else
{
  cerr << "error: "<< error << endl;

}

//Print the bitmap
  PrintMonochromeBitmap(face->glyph);
  FT_Done_Face(face);
   FT_Done_FreeType(library);

    return 0;

}