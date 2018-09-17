# ChangeLog.md

This documents notable or significant changes to
[ZetaGlest](https://zetaglest.github.io/). If you are looking for
information about the game from which it was forked, please see the
[MegaGlest home page](https://megaglest.org/).

## 2018-09-17

* CMakeLists.txt files have had a major tune-up (doesn't affect Windows users)

* The `mk/linux/build-zg.sh` and `mk/macos/build-zg.sh` scripts have
  been deprecated. See the
  [BUILD.md](https://github.com/ZetaGlest/zetaglest-source/blob/develop/BUILD.md)
  document for updated instructions.

* Except for Windows, The map editor, model viewer and import/export
  tools are no longer built by default. See BUILD.md for instructions on
  how to enable building them.

* BSD build instructions updated

* [INSTALL.md](https://github.com/ZetaGlest/zetaglest-source/blob/develop/INSTALL.md) document created

* man pages are no longer generated each time a build is performed.
  They must be manually generated when the help usage output is changed.

* debugging scripts have been moved to a scripts/ directory (they'll
  need reviewing and editing before use)

## 2018-09-07

Upgrade [libircclient](https://sourceforge.net/projects/libircclient/) embedded library from 1.3 to 1.10/
[view ChangeLog](https://github.com/ZetaGlest/zetaglest-source/commit/64cc6c3cb10c7fd6d97fa0af4a10b431100c58b0#diff-2a35002207d9e074987b668f273e598d)


## 2018-09-05

* Special effects added to fading/vanishing corpses


## 2018-09-04

* zoom-out restriction during network play removed
* added support for Windows 10 SDK


## 2018-09-03

* [[203]](https://github.com/ZetaGlest/zetaglest-source/issues/203)
Buildings will now still be built even when units are in the way

## 2018-06-28

* [transparency of the alpha component of textures can now be set](https://zetaglest.github.io/docs/modelling/textures.html#Transparency)/
[view patch](https://github.com/ZetaGlest/zetaglest-source/commit/b1760253fdb3e5b9b38c3bcf3d5f154044536b0c)

## 2018-06-10

* [[80]](https://github.com/ZetaGlest/zetaglest-source/issues/80)
Double right-clicking now sends a move command instead of attack
* [[#28]](https://github.com/ZetaGlest/zetaglest-source/issues/28)
Maximum unit selection removed
* [[#75]](https://github.com/ZetaGlest/zetaglest-source/issues/75)
Size of attack and move icons increased

## 2018-05-16

[16 maps added](https://github.com/ZetaGlest/zetaglest-data/compare/4c67d4bfba21...9dfb37450e07)

## 2018-05-08

OpenBSD build instructions added

## 2018-05-06

[[d1acd87](https://github.com/ZetaGlest/zetaglest-source/commit/d1acd8742395bca8b37656e9e8065022902586fe)]Lua
can now be used in scripts tag in faction tag within XML

## 2018-03-31

[[bugfix:835c6ef](https://github.com/ZetaGlest/zetaglest-source/commit/835c6efd924ed7e62ccd43e064bc6b7f5cdecbfc)]Fixed
"x" key getting stuck on Windows

## 2018-03-20

[[045b0b8](https://github.com/ZetaGlest/zetaglest-source/commit/045b0b88e051f7163fbef42fa0adc63a326ca186)]Removed "MG_" and "xxx" (3 digit extension) on nicknames in lobby player list

## 2018-03-14

[Windows](https://github.com/ZetaGlest/zetaglest-source/commits/develop/mk/windows) build
system, dependencies, and documentation updated

## 2018-02-22

* Some sound effects can now be customized by players. See
[diff](https://github.com/ZetaGlest/zetaglest-source/commit/73aa999de7f257b706f94c448a2fb7c2505fb746)
for detailed information, and see comments in
[glest.ini](https://github.com/ZetaGlest/zetaglest-source/blob/73aa999de7f257b706f94c448a2fb7c2505fb746/mk/linux/glest.ini#L98)

* These units can now heal mobile units from their own factions that are
in range

      nurse (British, radius of 15)
      archmage_tower (Magic, radius of 8)

See
[comparison](https://github.com/ZetaGlest/zetaglest-data/compare/e2d1ca55cb88...8762e708669e)
for detailed information and other related changes.

## 2018-02-16

* auto-healing radius changed from 8 to 15 (with the exception of Valhalla)

* Units standing near Valhalla (norse) are auto-healed (radius of 8)

## 2018-02-15

These units can now heal mobile units from their own factions that are
in range (radius of 8)

    priest (Egypt)
    wartime mechanic (Rome)
    minstrel (Elves)
    engineer (Greece)
    magician (Persia)

For more information about this change, see

https://github.com/ZetaGlest/zetaglest-data/compare/ac7d2af266cb...579ce1539bbb


## 2018-02-14

default command changed to "attack"

## 2018-02-03

Temporarily (or maybe permanently) reverted the default command back to
"move" (see entry dated 2018-01-27).

Hotkey changes:

    M -> H (Show console/chat history)
    H -> T (Toggle team chat
    T -> Z (Cycle between store units)
    M is now the hotkey for "move" when units are selected

## 2018-01-31

[Replaced the sphinx with the scarab](https://github.com/ZetaGlest/zetaglest-data/commit/60e734180ecb7f925144c94bef339e6130f9ae20)
(Egypt's starting units)

## 2018-01-27

[Changed default mouse right-click command: attack!](https://github.com/ZetaGlest/zetaglest-source/commit/2c4fc340de958f6b94b40ee62eabff015625e62b)
(pressing "a" not needed anymore); ["m" key can be used for "move"](https://github.com/ZetaGlest/zetaglest-source/commit/bf5a04be18f2b16b8a565acff4baabc5fbfed293).

I play-tested this earlier tonight. It takes some getting used to and
I'm not convinced yet it makes things better. We'll get more feedback.

## 2018-01-24

4 new tactical scenarios were added / Thanks @ [Julie Marchant](https://github.com/onpon4)

* Witches' Hunt
* Native Unrest
* Warlock Overlords
* Death Road

[#13](https://github.com/ZetaGlest/zetaglest-source/issues/13)
Observers no longer take up slots on a map. For instance, a map being
played by 4 players can have a 5th person observing; a map being played
by 8 people can have a 9th person observing. Up to 10 people can
connect, which mean you can have up to 6 observers with a 4-player map,
and 2 with an 8-player map.

There are some details to be worked out, but this feature seems to be
stable during testing. See the ticket (link above) for more
information.

## 2018-01-24

[#6](https://github.com/ZetaGlest/zetaglest-source/issues/6) Players
can now enter the multiplayer lobby unconditionally (i.e.
"InternetGamesAllowed" will no longer be used)

## 2018-01-14

Added Elves faction (https://forum.megaglest.org/index.php?topic=3944.0)

[#1] Replaced the Egypt graphics with
Archmage's remaster: https://github.com/virtushda/EgyptRemaster
