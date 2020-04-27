@echo off
set path_cli=%cd%
cd %path_cli%
echo Press [CTRL+C] to stop mining.
:begin
 ubicoin-cli.exe generate 1
goto begin