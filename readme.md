## CLASS DIAGRAM MAKER
**Class Diagram Maker** is a Qt/C++ application to that creates **Class Diagrams** 
from native C++ code. It was built as the  end of term project for college course on Object Oriented Programming.  
  
###Class Diagram
In software engineering, a class diagram in the Unified Modeling Language (UML) is a type of static structure diagram that describes the structure of a system by showing the system's classes, their attributes, operations (or methods), and the relationships among objects.   
(from Wikipedia)  
###Current Features
* Rightnow, this application makes class diagrams showing class-level _inheritence_ relationships. 
* It does not check the syntax. Comments etc are taken care of by the application.
* It can handle classes having any number of children
* Multiple Inheretance and structs are not supported currently
* Output is given in the form of a SVG file
### Sample Output
Output for code given in sampleCode.txt:  
**Note:** For clarity, screenshots of different portions of the generated SVG are provided here.  
  
######Classes without any inheretance relations  
![output1](https://github.com/hassaanakram/class-diagram-maker/tree/master/Samples/indepSample.jpg?raw=true)
  
######Classes that have inheretance relations  
![output1](https://github.com/hassaanakram/class-diagram-maker/tree/master/Samples/inhSample.jpg?raw=true)



