# CS451Final
Final For CS451 Fall 2019

In order to run, you need to have Xming Server Installed :

`https://sourceforge.net/projects/xming/`

and Xming Fonts installed :

`https://osdn.net/projects/sfnet_xming/downloads/Xming-fonts/7.7.0.10/Xming-fonts-7-7-0-10-setup.exe/`

Before entering the command line, start Xming, open the CLI and enter the following command :

`export DISPLAY=localhost:0.0`

## Compile

`gcc final.c -lm -lX11`

## Run

After running, it will prompt you for a degree of polynomial followed after a screen to plot your points.
Your number of points should be `degree + 1` minimum. Once you are done, click the colored bar on the right
to get your polynomial best fit.
