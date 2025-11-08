
#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>

using namespace std;

int main(){

  FT_Library library;
  FT_Face       face;

  FT_GlyphSlot  slot;
  FT_Matrix     matrix;                 /* transformation matrix */
  FT_Vector     pen;                    /* untransformed origin  */
  FT_Error      error;

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
        FT_Done_Face(face);
}

   FT_Done_FreeType(library);

    return 0;

}