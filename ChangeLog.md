# ChangeLog.md

This documents notable or significant changes to
[ZetaGlest](https://zetaglest.github.io/). If you are looking for
information about the game from which it was forked, please see the
[MegaGlest home page](https://megaglest.org/).

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
