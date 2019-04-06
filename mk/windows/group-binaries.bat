@echo off
md bin
md bin\vs2015
md bin\vs2017
md bin\vs2019

copy /y 7z.dll bin\vs2015\7z.dll
copy /y 7z.dll bin\vs2017\7z.dll
copy /y 7z.dll bin\vs2019\7z.dll

copy /y 7z.exe bin\vs2015\7z.exe
copy /y 7z.exe bin\vs2017\7z.exe
copy /y 7z.exe bin\vs2019\7z.exe

copy /y glest.ini bin\vs2015\glest.ini
copy /y glest.ini bin\vs2017\glest.ini
copy /y glest.ini bin\vs2019\glest.ini

copy /y ..\shared\glestkeys.ini bin\vs2015\glestkeys.ini
copy /y ..\shared\glestkeys.ini bin\vs2017\glestkeys.ini
copy /y ..\shared\glestkeys.ini bin\vs2019\glestkeys.ini

copy /y vs2015-32\g3d_viewer\g3d_viewer.exe bin\vs2015\g3d_viewer-32.exe
copy /y vs2017-32\g3d_viewer\g3d_viewer.exe bin\vs2017\g3d_viewer-32.exe
copy /y vs2017-32\g3d_viewer\g3d_viewer.exe bin\vs2019\g3d_viewer-32.exe

copy /y vs2015-32\map_editor\map_editor.exe bin\vs2015\map_editor-32.exe
copy /y vs2017-32\map_editor\map_editor.exe bin\vs2017\map_editor-32.exe
copy /y vs2017-32\map_editor\map_editor.exe bin\vs2019\map_editor-32.exe

copy /y vs2015-32\glest\glest.exe bin\vs2015\glest-32.exe
copy /y vs2017-32\glest\glest.exe bin\vs2017\glest-32.exe
copy /y vs2017-32\glest\glest.exe bin\vs2019\glest-32.exe

copy /y vs2015-64\g3d_viewer\g3d_viewer.exe bin\vs2015\g3d_viewer-64.exe
copy /y vs2017-64\g3d_viewer\g3d_viewer.exe bin\vs2017\g3d_viewer-64.exe
copy /y vs2017-64\g3d_viewer\g3d_viewer.exe bin\vs2019\g3d_viewer-64.exe

copy /y vs2015-64\map_editor\map_editor.exe bin\vs2015\map_editor-64.exe
copy /y vs2017-64\map_editor\map_editor.exe bin\vs2017\map_editor-64.exe
copy /y vs2017-64\map_editor\map_editor.exe bin\vs2019\map_editor-64.exe

copy /y vs2015-64\glest\glest.exe bin\vs2015\glest-64.exe
copy /y vs2017-64\glest\glest.exe bin\vs2017\glest-64.exe
copy /y vs2017-64\glest\glest.exe bin\vs2019\glest-64.exe