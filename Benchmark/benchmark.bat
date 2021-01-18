@ECHO OFF

setlocal EnableDelayedExpansion

echo No Structure
for /l %%x in (610, 10, 700) do (
	echo Generated sphere : %%x
	echo Generated sphere : %%x >> NoStructure_5.txt
	set "saveFileName=BenchImages\NoStructure_%%x.png"
	..\Synthese_TP2\out\build\x64-Release\Synthese_TP2.exe !saveFileName! %%x 0 false >> NoStructure_5.txt
)
echo.

echo Only Structure
for /l %%x in (610, 10, 700) do (
	echo Generated sphere : %%x
	echo Generated sphere : %%x >> OnlyStructure_5.txt
	set "saveFileName=BenchImages\OnlyStructure_%%x.png"
	..\Synthese_TP2\out\build\x64-Release\Synthese_TP2.exe !saveFileName! %%x 1 false >> OnlyStructure_5.txt
)
echo.

echo Mix Structure
for /l %%x in (610, 10, 700) do (
	echo Generated sphere : %%x
	echo Generated sphere : %%x >> MixStructure_5.txt
	set "saveFileName=BenchImages\MixStructure_%%x.png"
	..\Synthese_TP2\out\build\x64-Release\Synthese_TP2.exe !saveFileName! %%x 2 false >> MixStructure_5.txt
)
echo.

echo Finished