# Arduino FSM

This Repo provides an Example how to write a Finite-state machine (FSM) which can be nested.  
Based on this Wiki-Article: [Finite-state_machine](https://en.wikipedia.org/wiki/Finite-state_machine)

![FSM](Fsm_Moore_model_door_control.png)

## HowTo use Doxygen in VSCODE
Check out the generated HTML-File in doc.

## Install Doxygen
1. [Doxygen Installation manual](http://www.doxygen.nl/manual/install.html) 
2. Download a binary distribution at [Doxygen Download](http://www.doxygen.nl/download.html) 
3. Select "Full Installation" (default option) 
4. Add "c:/doxygen/bin" (or whatever path was used during the installation) to the System PATH   variable to run "doxygen" without providing the full path to the binary.  

[Source: [PALISADE](https://git.njit.edu/palisade/PALISADE/wikis/how-to-setup-doxygen-windows) 

## How to run doxygen

1. Start the doxywizard (Desktop App) 
2. Click on Flle->Open and choose the Doxyfile in the Folder Doc 
3. In Doxywizard switch to the Tab Run and Click on Run doxygen
4. When Doxygen has finished click on Show HTML output.  

## Usefull tips 
### Extension for VSCode
[Doxygen Documentation Generator](https://marketplace.visualstudio.com/items?itemName=cschlosser.doxdocgen)

Change the order in the Config-options. It's important that "author" appears befor "brief" becaus of an  display error in doxygen.

### How to Write Doxygen Doc Comments
[How to Write Doxygen Doc Comments](https://github.com/stan-dev/stan/wiki/How-to-Write-Doxygen-Doc-Comments)











