#include "Players.h"
#include "game.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

std::string PLAYERS::player_name() {
    std::string playername;
    std::cout << "Enter your name: ";
    std::cin >> playername;
    return playername;
}

std::string PLAYERS::cpu_name() {
    std::srand((unsigned)std::time(nullptr));
    std::vector<std::string> names = {
        "Admiral Splashface", "Captain Hullbreach", "Rear Admiral BoomBoom",
        "Ensign Bubbleblast", "Commander Keelhaul", "Captain Deckswabber",
        "Bosun Plankton", "Lieutenant Torpedoed", "Seaman Chumchucker",
        "Gunner Decksmasher", "Commander Reefwrack", "Ensign Minnow",
        "Captain ScatterShot", "Admiral Anchorpants", "Lieutenant SunkN",
        "Rear Admiral DudTorps", "Captain Fishbait", "Commander UnderHull",
        "Lieutenant Shipwrecker", "Seaman SquidInk", "Captain ClamCannon",
        "Admiral RustedChain", "Seaman BilgeRat", "Lieutenant SoggyBoots",
        "Commander SharkTooth", "Ensign Driftwood", "Captain WaveWhisper",
        "Rear Admiral MastCrack", "Gunner BarrelBlast", "Bosun SeaSlicer",
        "Admiral FogCutter", "Lieutenant DriftCurrent", "Commander DepthCharge",
        "Captain CannonClang", "Rear Admiral SternSlam", "Ensign Riptide",
        "Gunner TorpTosser", "Bosun AnchorDrop", "Lieutenant PortPlunder",
        "Captain HarborHaunt",
        "Admiral WaveCrusher", "Captain StormBreaker", "Commander SeaHunter", "Lieutenant DeckSmasher",
        "Bosun OceanWhisper", "Seaman TideRider", "Rear Admiral CoralWrath", "Gunner WaveStriker",
        "Ensign StormClash", "Captain DriftRider", "Commander ShipChaser", "Admiral MistBreaker",
        "Lieutenant DeepCurrent", "Seaman ReefBreaker", "Bosun HullBreaker", "Captain OceanFlare",
        "Commander TideCrusher", "Rear Admiral FleetHunter", "Ensign StormSurge", "Admiral SeaCannon",
        "Captain MistWalker", "Gunner DriftTorpedo", "Lieutenant DepthWrath", "Bosun SandDrifter",
        "Commander HullWrath", "Seaman WaveSmasher", "Admiral FogHunter", "Captain OceanStalker",
        "Rear Admiral CannonWrath", "Ensign DeckCutter", "Bosun DeepRider", "Commander MistStalker",
        "Admiral StormBreaker", "Captain CoralHunter", "Lieutenant HullSlicer", "Seaman DriftBreaker",
        "Gunner MistCrusher", "Commander ReefSlicer", "Bosun SandTide", "Lieutenant CannonSlammer",
        "Rear Admiral HullSmasher",
        "Commander StormSeeker", "Captain WaveWarden", "Lieutenant TideBreaker", "Bosun DriftClasher",
        "Rear Admiral OceanSlammer", "Admiral SeaRider", "Seaman DepthWalker", "Captain FogSurfer",
        "Ensign MistSlicer", "Gunner ReefHunter", "Lieutenant OceanCracker", "Bosun StormSurfer",
        "Admiral CannonCrusher", "Commander ReefWrath", "Seaman DeckBreaker", "Captain WaveCannon",
        "Commander MistRider", "Rear Admiral StormWrath", "Ensign TideHunter", "Admiral DeepCannon",
        "Captain CoralStalker", "Lieutenant DriftBreaker", "Seaman HullWrath", "Commander OceanSlicer",
        "Admiral SandCrusher", "Captain WaveSeeker", "Lieutenant StormRider", "Bosun DeepHunter",
        "Rear Admiral MistBreaker", "Seaman CoralCrusher", "Ensign OceanTide",
        "Captain HarborCrash", "Commander MistFlow", "Lieutenant DriftSlam", "Seaman CoralRider",
        "Admiral OceanSlash", "Captain WaveSlam", "Rear Admiral CannonClash", "Ensign StormTide",
        "Gunner DepthWrath", "Bosun AnchorBlast", "Seaman TideWrack", "Lieutenant DeckStrike",
        "Commander ReefSlam", "Captain FogHunter", "Admiral DepthBreak", "Ensign DriftFlare",
        "Gunner CoralCrash", "Bosun MistSlammer", "Seaman WaveCrusher", "Captain SandSlicer",
        "Lieutenant SeaBreaker", "Commander HarborSmash", "Rear Admiral OceanFury", "Bosun StormRider",
        "Captain FleetBreaker", "Commander TideWrack", "Lieutenant MistWalker", "Rear Admiral HullCutter",
        "Bosun FogCrusher", "Admiral DepthHunter", "Seaman ReefWrath", "Captain DriftCrusher",
        "Commander HarborCrusher", "Rear Admiral CoralSmash", "Lieutenant DeckWrack", "Bosun WaveCannon",
        "Admiral SandBreaker", "Seaman TideBreaker", "Captain OceanStalker", "Commander MistHunter",
        "Rear Admiral StormCrusher", "Ensign FogRider", "Lieutenant WaveSmash", "Gunner SandWrack",
        "Bosun CannonStrike", "Captain ReefRider", "Commander DriftHunter", "Rear Admiral SeaCrusher",
        "Admiral CoralStrike", "Lieutenant OceanFlare", "Captain TideWrack", "Bosun HarborSlicer",
        "Seaman FogBreaker", "Commander WaveHunter", "Admiral MistCrusher", "Rear Admiral SandTide",
        "Captain DepthWrack", "Ensign CoralHunter", "Bosun OceanStrike", "Lieutenant ReefSmasher",
        "Commander HarborWrath", "Captain TideCutter", "Rear Admiral DeckBreaker", "Seaman StormSlammer",
        "Admiral DriftHunter", "Commander FogSmasher", "Lieutenant SandCrush", "Bosun WaveWrack"
    };

    // Pick a random name
    std::string randomName = names[std::rand() % names.size()];
    std::cout << "CPU name: " << randomName << "\n";
    return randomName;
}


