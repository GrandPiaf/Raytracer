@ECHO OFF

setlocal EnableDelayedExpansion

echo No Structure
for /l %%x in (0, 10, 20) do (
	echo Generated sphere : %%x
	set "saveFileName=BenchImages\NoStructure_%%x.png"
	..\Synthese_TP2\out\build\x64-Release\Synthese_TP2.exe !saveFileName! %%x 0 false >> NoStructure.txt
)
echo.

echo Only Structure
for /l %%x in (0, 10, 20) do (
	echo Generated sphere : %%x
	set "saveFileName=BenchImages\OnlyStructure_%%x.png"
	..\Synthese_TP2\out\build\x64-Release\Synthese_TP2.exe !saveFileName! %%x 1 false >> OnlyStructure.txt
)
echo.

echo Mix Structure
for /l %%x in (0, 10, 20) do (
	echo Generated sphere : %%x
	set "saveFileName=BenchImages\MixStructure_%%x.png"
	..\Synthese_TP2\out\build\x64-Release\Synthese_TP2.exe !saveFileName! %%x 2 false >> MixStructure.txt
)
echo.

echo Finished