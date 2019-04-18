# DPTest
Test task for the Dynamic Pixels

## Player (FPS_Character)
Base class of player written with C++ (movement, actions etc.) and contains: 
- Movement Controller;
- Capsule Collision (inherit from Base Character); 
- Mesh Component (inherit from Base Character); 
- Camera Componnent. Attached to the HeadSocket (FPV_Camera) on the SkeletaMesh;
- Holding Componnent. Attached to the HandSocket and uses for Holding Actors of the WearableClass.

## Enemy (AI_Character)
Enemy class very similar to the Player class. It doesn't have a Camera Component. But It have uniq ID for each instance of AI_Character class.
ID using for calculate uniq position for each enemy around Player (using the rotate of the point at the Coordinate System);

## AI_Enemey_Controller
It cointains Behavior Component and Blackboard Component (For store reference for the Player instance 
and Mcguffin(instance of the Wearable Class);

## Wearable Actor
It Contains Statis Mesh only. Every character (FPS_Character and AI_Character) can Grab and Push objects of this class.
After Grab function Wearable Object attaching on the hand socket of Owner. 
Push funtion allow specify force and direction for "pushing" Object;

In-game classes (I'm using Blueprints for it) inherit from C++ classes and customize (movement speed, grab distance etc.).

## Enemy Life Cycle
For main life cycle of enemy using Task Object inherit from BTTask_Blackboard.
It contains different states (Finite Automata aka State Machine), rules for change state and initial value.
