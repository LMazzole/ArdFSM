# Arduino FSM

This Repo provides an Example how to write a Finite-state machine (FSM) which can be nested.  
Based on this Wiki-Article: [Finite-state_machine](https://en.wikipedia.org/wiki/Finite-state_machine) and an example from R.Bonderer (HSR)

<img src="https://raw.githubusercontent.com/LMazzole/ArdFSM/master/doxygen/Fsm_Moore_model_door_control.png" height="400" />

## Documentation with Doxygen

[View the GitHub-Page for Documentation](https://lmazzole.github.io/ArdFSM/)

## HowTo use Doxygen in VSCODE

## Install Doxygen
[Doxygen Installation manual](http://www.doxygen.nl/manual/install.html) 
1. Download a binary distribution at [Doxygen Download](http://www.doxygen.nl/download.html) 
2. Select "Full Installation" (default option) 
3. Add "c:/doxygen/bin" (or whatever path was used during the installation) to the System PATH   variable to run "doxygen" without providing the full path to the binary.  

[Source: [PALISADE](https://git.njit.edu/palisade/PALISADE/wikis/how-to-setup-doxygen-windows) ]

## How to run doxygen

1. Start the doxywizard (Desktop App) 
2. Click on Flle->Open and choose the Doxyfile in the Folder Doc 
3. In Doxywizard switch to the Tab Run and Click on Run doxygen
4. When Doxygen has finished click on Show HTML output.  

[Source: [PALISADE](https://git.njit.edu/palisade/PALISADE/wikis/how-to-setup-doxygen-windows) ]

## Doxygen and GitHub-Pages

[ToDo]

## Usefull tips 
### Extension for VSCode
[Doxygen Documentation Generator](https://marketplace.visualstudio.com/items?itemName=cschlosser.doxdocgen)

Change the order in config-options. It's important that "author" appears befor "brief" because of an  parse error in doxygen.

### How to Write Doxygen Doc Comments
[How to Write Doxygen Doc Comments](https://github.com/stan-dev/stan/wiki/How-to-Write-Doxygen-Doc-Comments)











