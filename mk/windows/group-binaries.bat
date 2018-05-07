@echo off
md bin
md bin\vs2015
md bin\vs2017

copy /y 7z.dll bin\vs2015\7z.dll
copy /y 7z.dll bin\vs2017\7z.dll

copy /y 7z.exe bin\vs2015\7z.exe
copy /y 7z.exe bin\vs2017\7z.exe

copy /y glest.ini bin\vs2015\glest.ini
copy /y glest.ini bin\vs2017\glest.ini

copy /y ..\shared\glestkeys.ini bin\vs2015\glestkeys.ini
copy /y ..\shared\glestkeys.ini bin\vs2017\glestkeys.ini

copy /y ..\shared\servers.ini bin\vs2015\servers.ini
copy /y ..\shared\servers.ini bin\vs2017\servers.ini

copy /y vs2015-32\g3d_viewerWin32\Release\g3dviewer.exe bin\vs2015\g3dviewer-32.exe
copy /y vs2017-32\g3d_viewerWin32\Release\g3dviewer.exe bin\vs2017\g3dviewer-32.exe

copy /y vs2015-32\map_editorWin32\Release\map_editor.exe bin\vs2015\map_editor-32.exe
copy /y vs2017-32\map_editorWin32\Release\map_editor.exe bin\vs2017\map_editor-32.exe

copy /y vs2015-32\zetaglest\zetaglest.exe bin\vs2015\zetaglest-32.exe
copy /y vs2017-32\zetaglest\zetaglest.exe bin\vs2017\zetaglest-32.exe

copy /y vs2015-64\g3dviewerx64\Release\g3dviewer.exe bin\vs2015\g3dviewer-64.exe
copy /y vs2017-64\g3dviewerx64\Release\g3dviewer.exe bin\vs2017\g3dviewer-64.exe

copy /y vs2015-64\map_editorx64\Release\map_editor.exe bin\vs2015\map_editor-64.exe
copy /y vs2017-64\map_editorx64\Release\map_editor.exe bin\vs2017\map_editor-64.exe

copy /y vs2015-64\zetaglest\zetaglest.exe bin\vs2015\zetaglest-64.exe
copy /y vs2017-64\zetaglest\zetaglest.exe bin\vs2017\zetaglest-64.exe