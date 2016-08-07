##*About This Project*
This respository is for all files related to modifications of the [Sea Perch](www.seaperch.org) ROV. The overall goals of this project are to:
* Make the vehicle controllable from a microcontroller or computer.
* Enable the vehicle to have the potential to be self contained. This includes:
  * Making the controller waterproof so it can be deployed on the vehicle,
  * Making the battery waterproof so it can go on the vehicle,
  * Writing autonomy scripts for the vehicle.
* Make the vehicle 'smart', including:
  * Autonomy, regardless of controller location (land or vehicle)
  * Sensor integration (IMUs...)
* Anything else we think of as we go.

##*Organization*
###Software Directory
The Software directory houses all of the code, Arduino or otherwise, associated with this project. It have two main subdirectories: Vehicle and Computer.
####Vehicle
The Vehicle subdirectory is for all sketches that are to be uploaded to the vehicle controller Arduino.
####Computer
The Computer subdirectory is for all support software that may exist. This could potentially be remote interfaces, wireless command sequence uploaders, command generators and much more.
###Electrical Directory
The Electrical directory is for schematics eagle design files and related to designing the vehicle controller. Additionally it should include parts lists and assembly processes if applicable.
###Hardware Directory
The Hardware Design directory is for potential CAD design files for the main structure of the vehicle.


##*Resources*
* [Google Drive folder](https://drive.google.com/folderview?id=0B45sdQ03G0k-UUpMSS1selFKa1k&usp=sharing) 
* [Sea Perch](www.seaperch.org) 
* [Sea Perch BOM](http://www.seaperch.org/Parts_List) (Note: requires free account) 
* [Sparkfun](www.sparkfun.com) (Parts) 
