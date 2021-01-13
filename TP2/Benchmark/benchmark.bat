@ECHO OFF

(
	echo Parameters are : 10
	echo.
) > result.txt

for /l %%x in (1, 1, 2) do (
   echo Calcul numero : %%x
   ..\Synthese_TP2\out\build\x64-Release\Synthese_TP2.exe >> result.txt
)

echo Finished