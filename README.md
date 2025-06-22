# Unreal Engine 4 C++ Mini AI Project

This is a small Unreal Engine 4 project made in C++ as part of a mini course "C++ for Blueprinters".  
The main idea is to create a simple AI enemy that can see the player and chase them using a basic AIController and NavMesh.

---

## What’s inside?

- Custom **Character** class for the player with basic movement and camera  
- Custom **AI** character that uses sight to detect and chase the player  
- AI Controller with basic perception (Sight sense)  
- Use of **NavMesh** for AI navigation  
- Fully implemented in clean C++ (no Behavior Trees)  
- Built for Unreal Engine 4.25.4

---

## How to use

1. Open the project in Unreal Editor  
2. Make sure there is a `NavMeshBoundsVolume` in the scene covering the playable area  
3. Play the game and test the AI’s vision and chasing behavior  
4. Adjust AI parameters (speed, sight radius, field of view) in Blueprints or C++ code

---

## Useful links

- [C++ for Blueprinters - Epic Games tutorial](https://dev.epicgames.com/community/learning/tutorials/qO/c-for-blueprinters)  
- [Unreal Engine NavMesh Documentation](https://docs.unrealengine.com/4.27/en-US/InteractiveExperiences/Navigation/)

---

## Author

This project was created by Andrija Stanisic as part of a personal mini course and Unreal Engine C++ learning journey.

---

Thanks for checking it out! Feel free to reach out if you have any questions.
