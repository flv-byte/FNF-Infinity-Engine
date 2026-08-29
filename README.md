# ∞ Infinity Engine

> **A modular, C++ game engine built from the ground up.**

Infinity Engine is a lightweight, modular game engine focused on giving FNF a clean foundation for rendering, scenes, addons, input, assets, and runtime systems.

It started as the foundation for **FLV FNF**, but evolved into something bigger:

**an engine that can keep growing.** ♾️

---

## 🪪 Credits

This project was heavily inspired by the work of other people:
* **Friday Night Funkin' - FunkinCrew (<33333)**
* **Psych Engine - ShadowMario**
* **Psych Engine Online - Snirozu**

---

## ✨ Features

### 🎨 Renderer

* SDL3-based rendering
* Virtual coordinate system
* Automatic aspect-ratio handling
* Resolution-independent positioning
* Rectangle and texture rendering
* Optional render information
* Renderer abstraction for different implementations

### 🎬 Scene System

Scenes represent the current state of the game.

They can be:

* Created dynamically
* Destroyed dynamically
* Switched at runtime
* Identified through unique UIDs
* Multiple instances of the same scene type

This means the engine isn't limited to simply hiding and showing predefined screens.

**Scenes can actually come and go at runtime.**

### 🧩 Addons

Addons are persistent runtime systems that execute independently of the current scene.

They can be used for things such as:

* FPS counters
* Chat
* Download managers
* Notifications
* Debug overlays
* Network systems
* Other background tasks

An addon doesn't need to belong to a specific scene.

A scene can disappear.

**The addon keeps going.**

### 🎮 Input

A dedicated input system designed to keep input handling separate from individual scenes and gameplay logic.

### 📦 Asset Management

Centralized asset handling designed to make loading and managing game resources easier as projects grow.

### 🛠️ Built for Expansion

Infinity Engine is designed around modular systems rather than forcing everything into one giant game loop.

The goal is simple:

> **Build the foundation once. Build the game on top of it.**

---

## 🏗️ Architecture

A simplified view of the engine:

```text
                         Runtime
                            │
              ┌─────────────┴─────────────┐
              │                           │
        SceneManager                 AddonManager
              │                           │
        Current Scene                 All Addons
              │                           │
        ┌─────┴─────┐              ┌──────┼──────┐
        │           │              │      │      │
     Update      Render          Tick   Tick   Tick
        │           │              │      │      │
        └───────────┴──────────────┴──────┴──────┘
                            │
                         Renderer
                            │
                           SDL3
```

The important distinction is:

**Scenes represent switchable game state.**

**Addons represent persistent runtime systems.**

---

## 🚀 Current Status

Infinity Engine is currently under active development.
While still being in a very early stage, the engine will have a long way to go.

The foundation is being built piece by piece, with the renderer and scene architecture already taking shape.

Current work includes:

* [x] SDL3 window initialization
* [x] Renderer abstraction
* [x] Virtual coordinates
* [x] Aspect-ratio handling
* [x] Window resize handling
* [x] Basic line rendering
* [x] Render information
* [x] Scene identification
* [x] Dynamic scene management
* [x] Scene switching
* [ ] Input manager
* [ ] Asset manager
* [ ] Addon manager
* [ ] Custom scripting integration
* [ ] Audio system
* [ ] More rendering functionality
* [ ] Scene switching improvements
* [ ] Gameplay systems

This list will probably grow.

**A lot.** ♾️

---

## 🎮 The Original Goal

Infinity Engine is being developed alongside **FLV FNF**, a personal FNF-inspired game project, bringing to life other features that **actually** funk up the game!

The engine exists so the game doesn't have to reinvent its foundation every time something new is added.

Instead of:

```text
Game
└── Everything
```

the goal is:

```text
Infinity Engine
├── Renderer
├── Runtime
├── Scene System
├── Addon System
├── Input
├── Assets
└── Other Core Systems
        │
        ▼
      Game
```

---

## 🧪 Development Philosophy

Infinity Engine is built around a few simple ideas:

**Keep systems separated.**

**Keep interfaces simple.**

**Don't make a scene responsible for things that aren't its job.**

**Make runtime systems reusable.**

And most importantly:

> **If the engine needs a feature, build it into the foundation instead of duct-taping it onto the game.**

---

## 🔧 Building

Infinity Engine currently uses:

* **C++**
* **CMake**
* **SDL3**
* **Visual Studio** on Windows

Clone the repository, configure the CMake project, build, and run.

More detailed build instructions will be added as the project matures.

---

## 🗺️ Roadmap

### Phase 1 — Foundation

> Make the engine actually exist.

* Renderer
* Runtime
* Virtual coordinates
* Scene manager
* Input
* Asset management
* Addons

### Phase 2 — Game Systems

> Make games possible.

* Audio
* Text rendering
* UI
* Animation
* Interpreted language scripting
* More asset types
* Better scene management
* Mod support

### Phase 3 — FLV FNF

> Make the game.

* Main menu
* Song selection
* Gameplay
* Notes
* Scoring
* Weeks
* Multiplayer

### Phase ∞

> Whatever happens next.

---

## 📜 License

See [`LICENSE`](LICENSE) for the license of Infinity Engine.

Game assets, music, and other third-party content may have separate licenses.

---

## 🪿 A Note From Development

This engine is being built one system at a time.

Fueled by the feeling of making something work.

Fueled by the fact that it works.

Sometimes that means spending an unreasonable amount of time making textures render correctly.

Sometimes it means fighting C++.

Sometimes it means staring at CMake wondering what you did wrong.

Sometimes it means bashing your head at AI hoping it will fix all your bugs.

But eventually:

```text
compile
   ↓
run
   ↓
window appears
   ↓
something renders
   ↓
:D
```

And that's pretty funkin' cool.

**Welcome to Infinity Engine.** ♾️
