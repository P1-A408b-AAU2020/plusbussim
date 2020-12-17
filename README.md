# plusbussim

<!-- Link to github page: https://github.com/P1-A408b-AAU2020/plusbussim with a better README file-->

<a href= "https://github.com/P1-A408b-AAU2020/plusbussim">
GitHub page
</a>


To compile the program using the gcc compiler, type the following command in terminal:

- gcc simulation.c debug.c debug.h node.c node.h trafficlights.c trafficlights.h

The program can then be run and will display how long the simulation took.

## Setup and changeable variables
These Variables can be changed for different conditions. All these variables is found in **node.h**:

To print the simulation as the simulation happens assign **DEBUG** to **1** in **node.h**.

- **Print simulation of roads**: Set **DEBUG** to **1**

- **Changing vehicle amount**: Change **AMOUNT_VEHICLES** to wanted amount

- **Changing how many vehicles should be initiated at startup**: Change **INIT_PERCENTAGE** to **0.X**
	- Values must not exceed 1

- **Simulate Plusbus**: 
     - **PLUS_OR_BUS** should be assigned to **1**
     - **END_LINK** should be assigned to **59**

- **Simulate conventional bus**:
     - **PLUS_OR_BUS** should be assigned to **0**
     - **END_LINK** should be assigned to **58**
  

## Description of files

- **.h** files are header files to the **.c** file with the same name. e.g. **node.h** is the header file to **node.c**.

- **simulation.c** is where the simulation happens, here the vehicles are moved, their speed is changed, new vehicles are instantiated etc. This is the Agent Layer in the Multi Agent System besides the traffic agent which has it's own file **trafficlights.c**. In **simulation.c** main is located, and that is why there is not a **simulation.h**.

- **node.c** is where the simulation environment is created. Here the nodes are constructed with the links, and the next link for a vehicle is calculated in here based on its turn_direction. This is the first layer in the Multi Agent System.

- **trafficlights.c** is where the traffic light agent is. Here everything around the traffic lights happens.

- **debug.c** is the interface layer. This is where everything is printed out to the user.






