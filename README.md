# POCKETBOOK DOOM
## Description
This is port of first doom to pocketbook, adapted for <b>basic 3</b> model, based on <a href="https://github.com/ozkl/doomgeneric">doom generic</a> source.

## Building
For building you need to run <b>makearm.sh</b> script. In case of any problems related to linking stage you need to modify <b>link.txt</b> file and delete
``` ,--dependency-file=CMakeFiles/{can be different}/link.d  ``` </br>Also don't forget about pocketbook sdk :) </br>
You can find it <a href="https://github.com/blchinezu/pocketbook-sdk/tree/master">here</a>. Project must be in <b>sources</b> folder.

## Installation
Just copy <b>doom.wad</b> and executable to <b>applications</b> dir inside your pocketbook device. 