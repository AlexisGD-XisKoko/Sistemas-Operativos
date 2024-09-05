@echo off 
rem Informacio personal del equipo 
echo -------------------------
echo	Los Papois
echo	version 2.0
echo	Fecha: 04/09/24
echo.
echo Este programa convierte un numero decimal a hexadecimal 
echo -------------------------
echo.
pause  rem Pausa para que el usuario pueda leer la informacion 

:menu 
cls 
echo ------------------------
echo CONVERSION DECIMAL A HEXADECIMAL 
echo ------------------------
echo.
echo 1. Convertir un numero decimal a hexadecimal 
echo 2. Convertir un numero decimal a binario
echo 3.Salir 

echo. 

set /p choice=Selecciona una opcion (1-3):

if "%choice%"=="1" goto convertir 
if "%choice%"=="2" goto cambiar
if "%choice%"=="3" goto salir
goto menu:

:convertir
cls 
set /p decimal=Introduce un numero decimal:

rem Realizamos la conversion usando powershell
for /f "delims=" %%A in ('powershell "[convert]::ToString(%decimal%, 16)"') do set hexadecimal=%%A

echo.
echo El numero hexadecimal es:%hexadecimal%
echo.
pause
goto menu

:cambiar
cls
echo ----completa el codigo por favor----
echo 	Atte. Los Papois :) 
echo.
pause
goto menu

:salir
exit






