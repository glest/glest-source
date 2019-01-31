// This file is part of Glest <https://github.com/Glest>
//
// Copyright (C) 2018  The Glest team
//
// Glest is a fork of MegaGlest <https://megaglest.org/>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>

#ifndef _TILESET_H_
#define _TILESET_H_

#ifdef WIN32
#include <winsock2.h>
#include <winsock.h>
#endif

#include <map>
#include "graphics_interface.h"
#include "xml_parser.h"
#include "object_type.h"
#include "sound.h"
#include "randomgen.h"
#include "surface_atlas.h"
#include "checksum.h"
#include "leak_dumper.h"

namespace Game {
	using Shared::Xml::XmlNode;
	using Shared::Sound::StaticSound;
	using Shared::Sound::StrSound;
	using Shared::Graphics::Model;
	using Shared::Graphics::Vec3f;
	using Shared::Graphics::Texture2D;
	using Shared::Graphics::Texture3D;
	using Shared::Util::RandomGen;
	using Shared::Util::Checksum;

	using std::map;

	enum FogMode {
		fmExp,
		fmExp2
	};

	enum Weather {
		wSunny,
		wRainy,
		wSnowy
	};

	class Renderer;
	class SurfaceCell;

	// =====================================================
	//	class AmbientSounds
	// =====================================================

	class AmbientSounds {
	private:
		bool enabledDay;
		bool enabledNight;
		bool enabledRain;
		bool enabledSnow;
		bool enabledDayStart;
		bool enabledNightStart;
		bool alwaysPlayDay;
		bool alwaysPlayNight;
		StrSound day;
		StrSound night;
		StrSound rain;
		StrSound snow;
		StaticSound dayStart;
		StaticSound nightStart;

	public:
		AmbientSounds() {
			enabledDay = false;
			enabledNight = false;
			enabledRain = false;
			enabledSnow = false;
			enabledDayStart = false;
			enabledNightStart = false;
			alwaysPlayDay = false;
			alwaysPlayNight = false;
		}

		bool isEnabledDay() const {
			return enabledDay;
		}
		bool isEnabledNight() const {
			return enabledNight;
		}
		bool isEnabledRain() const {
			return enabledRain;
		}
		bool isEnabledSnow() const {
			return enabledSnow;
		}
		bool isEnabledDayStart() const {
			return enabledDayStart;
		}
		bool isEnabledNightStart() const {
			return enabledNightStart;
		}
		bool getAlwaysPlayDay() const {
			return alwaysPlayDay;
		}
		bool getAlwaysPlayNight() const {
			return alwaysPlayNight;
		}

		StrSound *getDay() {
			return &day;
		}
		StrSound *getNight() {
			return &night;
		}
		StrSound *getRain() {
			return &rain;
		}
		StrSound *getSnow() {
			return &snow;
		}
		StaticSound *getDayStart() {
			return &dayStart;
		}
		StaticSound *getNightStart() {
			return &nightStart;
		}

		void load(const string &dir, const XmlNode *xmlNode,
			std::map<string, vector<pair<string, string> > > &loadedFileList, string parentLoader);
	};

	// =====================================================
	// 	class Tileset
	//
	///	Containt textures, models and parameters for a tileset
	// =====================================================

	class Tileset {
	public:
		static const int waterTexCount = 1;
		static const int surfCount = 6;
		static const int objCount = 10;
		static const int transitionVars = 2; //number or different transition textures
		static const float standardAirHeight;
		static const float standardShadowIntensity;

	public:
		typedef vector<float> SurfProbs;
		typedef vector<Pixmap2D *> SurfPixmaps;

	private:
		SurfaceAtlas surfaceAtlas;
		ObjectType objectTypes[objCount];

		SurfProbs surfProbs[surfCount];
		SurfPixmaps surfPixmaps[surfCount];

		int partsArray[surfCount];
		//int partsizes[surfCount];

		RandomGen random;
		Texture3D *waterTex;
		bool waterEffects;
		bool fog;
		int fogMode;
		float fogDensity;
		Vec3f fogColor;
		Vec3f sunLightColor;
		Vec3f moonLightColor;
		float shadowIntensity;
		Weather weather;
		float airHeight;

		AmbientSounds ambientSounds;
		Checksum checksumValue;

		string tileset_name;

	public:
		Tileset() {
			waterTex = NULL;
			waterEffects = false;
			fog = false;
			fogMode = 0;
			fogDensity = 0.0f;
			weather = wSunny;
			airHeight = standardAirHeight;
			shadowIntensity = standardShadowIntensity;

			for (int index = 0; index < surfCount; ++index) {
				partsArray[index] = 0;
			}
		}
		~Tileset();
		Checksum loadTileset(const vector<string> pathList, const string &tilesetName,
			Checksum* checksum, std::map<string, vector<pair<string, string> > > &loadedFileList);
		void load(const string &dir, Checksum *checksum, Checksum *tilesetChecksum,
			std::map<string, vector<pair<string, string> > > &loadedFileList);
		Checksum * getChecksumValue() {
			return &checksumValue;
		}

		//get
		float getAirHeight()const {
			return airHeight;
		}
		const SurfaceAtlas *getSurfaceAtlas() const {
			return &surfaceAtlas;
		}
		ObjectType *getObjectType(int i) {
			return &objectTypes[i];
		}
		float getSurfProb(int surf, int var) const {
			return surfProbs[surf][var];
		}
		Texture3D *getWaterTex() const {
			return waterTex;
		}
		bool getWaterEffects() const {
			return waterEffects;
		}
		bool getFog() const {
			return fog;
		}
		int getFogMode() const {
			return fogMode;
		}
		float getFogDensity() const {
			return fogDensity;
		}
		const Vec3f &getFogColor() const {
			return fogColor;
		}
		const Vec3f &getSunLightColor() const {
			return sunLightColor;
		}
		const Vec3f &getMoonLightColor() const {
			return moonLightColor;
		}
		float getShadowIntense()const {
			return shadowIntensity;
		}
		Weather getWeather() const {
			return weather;
		}
		void setWeather(Weather value) {
			weather = value;
		}

		//surface textures
		const Pixmap2D *getSurfPixmap(int type, int var) const;
		void addSurfTex(int leftUp, int rightUp, int leftDown, int rightDown, Vec2f &coord, const Texture2D *&texture, int mapX, int mapY);

		//sounds
		AmbientSounds *getAmbientSounds() {
			return &ambientSounds;
		}

		string getName() const {
			return tileset_name;
		}
	};

} //end namespace

#endif
