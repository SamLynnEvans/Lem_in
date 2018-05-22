# Lem_in

Lem_in brings ants from a start room to an end room in the shortest amount of turns possible.

A dynamic application of the Dijkstra shortest path algorithm ensures that all paths to the end room are found, and the ants are split among them according to each route's distance.

Usage:
./lem_in < map

Maps are simple text files and must be formatted like the following example:

15<br/>
##start<br/>
start 16 3<br/>
2 16 7<br/>
3 16 3<br/>
4 16 5<br/>
5 9 3<br/>
6 1 5<br/>
7 4 8<br/>
##end<br/>
goal_room 9 5<br/>
goal_room-4<br/>
goal_room-6<br/>
start-3<br/>
4-3<br/>
5-2<br/>
3-5<br/>
4-2<br/>
2-start<br/>
7-6<br/>
7-2<br/>
7-4<br/>
6-5<br/>
#example comment

The first line contains the number of ants. The rooms are then declared, formatted as 'name X-coordinate Y-coordinate'. The ##start and ##end commands tell the program the following room will be the start and end room respectively. Finally, the rooms are linked together to create the possible paths for the ants to take. More sample maps can be found in the <a href="https://github.com/SamLynnEvans/Lem_in/tree/master/maps">maps folder</a>.

Lem_in will output the turn-based movement of ants. Each ant can move one room at a time, and no two ants can occupy one room at the same time (apart form the start and end room). Each line represents one turn. The output of the above map would look like this.

L1-2 L2-3<br/>L1-4 L2-5 L3-2 L4-3<br/>L1-goal_room L2-6 L3-4 L4-5 L5-2 L6-3<br/>L2-goal_room L3-goal_room L4-6 L5-4 L6-5 L7-2 L8-3<br/>L4-goal_room L5-goal_room L6-6 L7-4 L8-5 L9-2 L10-3<br/>L6-goal_room L7-goal_room L8-6 L9-4 L10-5 L11-2 L12-3<br/>L8-goal_room L9-goal_room L10-6 L11-4 L12-5 L13-2 L14-3<br/>L10-goal_room L11-goal_room L12-6 L13-4 L14-5 L15-2<br/>L12-goal_room L13-goal_room L14-6 L15-4<br/>L14-goal_room L15-goal_room<br/>

Key L1-3 : ant 1 moves to room 3.

<b>Visualiser</b>

Call the visualiser by entering the vis folder, typing make, and entering the command:

../lem-in < ../maps/map_of_your_choice

Once the visualiser is running use the right and left arrows to move a turn forward or backward respectively. Press Escape key to exit.

<b>Learnings</b>
