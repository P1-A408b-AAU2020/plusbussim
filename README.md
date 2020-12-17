# plusbussim
The purpose of this project is to simulate the Plusbus, a BRT system which opens in Aalborg, Denmark in 2023.

<a href= "https://github.com/P1-A408b-AAU2020/plusbussim">
GitHub link 
</a>

To compile the program using the gcc compiler, type the following command in terminal
<p align = "center">
gcc simulation.c debug.c debug.h node.c node.h trafficlights.c trafficlights.h
</p>
The program can then be run and will display how long the simulation took.

## Change simulation and print
### Print
To print the simulation as the simulation happens assign **DEBUG** to **1** in **node.h**.

### Change simulation
To change between simulating the bus and the plusbus, the following changes should be made in **node.h**:


- **Simulate Plusbus**: 
     - **PLUS_OR_BUS** should be assigned to **1**
     - **END_LINK** should be assigned to **59**

- **Simulate conventional bus**:
     - **PLUS_OR_BUS** should be assigned to **0**
     - **END_LINK** should be assigned to **58**
  



## Description of files

- **.h** files are header files to the **.c** file with the same name. e.g. **node.h** is the header file to **node.c**.

- **simulation.c** is where the simulation happens, here the vehicles are moved, their speed is changed, new vehicles are instantiated etc. This is the Agent Layer in the Multi Agent System besides the traffic agent which has it's own file **trafficlights.c**. In **simulation.c** main is located, and that is why there is not a **simulation.h**

- **node.c** is where the simulation environment is created. Here the nodes are constructed with the links, and the next link for a vehicle is calculated in here based on its turn_direction. This is the first layer in the Multi Agent System.

- ****






