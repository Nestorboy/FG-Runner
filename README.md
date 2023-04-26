# FG-Runner

## Features
- [x] Simple inputs.<br>
- [x] Health points.<br>
- [x] Infinitely repeating ground segments.<br>
- [x] Stationary obstacles with variation.<br>
- [x] Increasing speed over time.<br>
- [ ] Point system.
- [ ] Killable enemies.
- [ ] Menus.
- [ ] Saved scoreboard.

## Part 1
All the code so far has been written using C++ centered around OOP in the context of the Unreal Engine.
The programs are designed such that they can be extended in the future, and I've got plans to tweak them a bit in order to use inheritance for components that share their behaviours.

The first class I began working on was the RunnerCharacter, who's able to interpolate between a fixed amount of lanes which can be defined in its blueprint. The inputs are pretty simple for now, but should lend the user enough control in order to avoid any upcoming obstacles. The RunnerCharacter also has health which can be configured in the blueprint, but currently there's no code to handle what happens once the player runs out of health.

There's a SegmentManager which creates, maintains and removes GroundSegments once their life cycles end. This manager is responsible for lining up the segments during creation, moving them at a defined speed and also marking them for removal once they reach a certain threshold. It's also got some parameters which can be tweaked in order to avoid having to recompile due to small value changes.

A GroundSegment isn't responsible for much apart from being a surface that the player is able to stand on. GroundSegments do have a user-defined entry and exit point which I use in order to seamlessly stitch them together, leaving no gap or overlapping visible. The entry and exit points also help aid in determining how long a GroundSegment is, which could be helpful in the future.

The ObstacleBase class is intended to be derived from in order to make a component that damages the player once they overlap them. The ObstacleBase also comes with some simple veriety for now, since I haven't finished writing the derived classes. First there's a user-defined probability which determines how big of a chance the ObstacleBase has to actually appear when it's created. Secondly there's locational variety, where the location of the ObstacleBase is aligned with one of the lanes with equal probability. Lastly there's some rotational variety where the yaw is randomized between a lower and upper bound which is currently hardcoded as I forgot to to expose it as a property.

## Part 2
