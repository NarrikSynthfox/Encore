#pragma once

#include "assets.h"

player player;

void Assets::DrawTextRubik32(const char* text, float posX, float posY, Color color)  {
    DrawTextEx(rubik32, text, { posX,posY }, 32, 1, color);
}
void Assets::DrawTextRubik(const char* text, float posX, float posY, float fontSize, Color color)  {
    DrawTextEx(rubik, text, { posX,posY }, fontSize, 1, color);
}
void Assets::DrawTextRHDI(const char* text, float posX, float posY, Color color)  {
    DrawTextEx(redHatDisplayItalic, text, { posX,posY }, 48, 1, color);
}
float Assets::MeasureTextRubik32(const char* text)  {
    return MeasureTextEx(rubik32, text, 32, 1.0f).x;
}
float Assets::MeasureTextRubik(const char* text, float fontSize)  {
    return MeasureTextEx(rubik, text, fontSize, 1.0f).x;
}
float Assets::MeasureTextRHDI(const char* text)  {
    return MeasureTextEx(redHatDisplayItalic, text, 48, 1.0f).x;
}

Texture2D Assets::LoadTextureFilter(const std::filesystem::path& texturePath) {
    Texture2D tex = LoadTexture(texturePath.string().c_str());
    SetTextureFilter(tex, TEXTURE_FILTER_TRILINEAR);
    return tex;
}

void Assets::loadAssets(const std::filesystem::path &directory) {
    smasherReg = LoadModel((directory / "Assets/highway/smasher.obj").string().c_str());
    smasherRegTex = Assets::LoadTextureFilter(directory / "Assets/highway/smasher_reg.png");
    smasherReg.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = smasherRegTex;
    smasherReg.materials[0].maps[MATERIAL_MAP_ALBEDO].color = WHITE;
    smasherReg.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = smasherRegTex;
    smasherReg.materials[0].maps[MATERIAL_MAP_ALBEDO].color = WHITE;

    smasherBoard = LoadModel((directory / "Assets/highway/new_board.obj").string().c_str());
    smasherBoardTex = LoadTextureFilter(directory / "Assets/highway/smasher_board_new.png");
    smasherBoard.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = smasherBoardTex;
    smasherBoard.materials[0].maps[MATERIAL_MAP_ALBEDO].color = LIGHTGRAY;
    smasherBoardEMH = LoadModel((directory / "Assets/highway/board_emh.obj").string().c_str());
    smasherBoardEMH.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = smasherBoardTex;
    smasherBoardEMH.materials[0].maps[MATERIAL_MAP_ALBEDO].color = LIGHTGRAY;

    lanes = LoadModel((directory / "Assets/highway/lanes.obj").string().c_str());
    lanesTex = LoadTextureFilter(directory / "Assets/highway/lanes.png");
    lanes.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = lanesTex;
    lanes.materials[0].maps[MATERIAL_MAP_ALBEDO].color = WHITE;

    smasherPressed = LoadModel((directory / "Assets/highway/smasher.obj").string().c_str());
    smasherPressTex = LoadTextureFilter(directory / "Assets/highway/smasher_press.png");
    smasherPressed.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = smasherPressTex;
    smasherPressed.materials[0].maps[MATERIAL_MAP_ALBEDO].color = WHITE;

    star = LoadTextureFilter(directory/ "Assets/ui/star.png");
    goldStar = LoadTextureFilter(directory/ "Assets/ui/gold-star.png");
    emptyStar = LoadTextureFilter(directory/ "Assets/ui/empty-star.png");

    odFrame = LoadModel((directory / "Assets/ui/od_frame.obj").string().c_str());
    odBar = LoadModel((directory / "Assets/ui/od_fill.obj").string().c_str());
    multFrame = LoadModel((directory / "Assets/ui/multcircle_frame.obj").string().c_str());
    multBar = LoadModel((directory / "Assets/ui/multcircle_fill.obj").string().c_str());
    multCtr3 = LoadModel((directory / "Assets/ui/multbar_3.obj").string().c_str());
    multCtr5 = LoadModel((directory / "Assets/ui/multbar_5.obj").string().c_str());
    multNumber = LoadModel((directory / "Assets/ui/mult_number_plane.obj").string().c_str());
    odMultFrame = LoadTextureFilter(directory / "Assets/ui/mult_base.png");
    odMultFill = LoadTextureFilter(directory / "Assets/ui/mult_fill.png");
    odMultFillActive = LoadTextureFilter(directory / "Assets/ui/mult_fill_od.png");
    multNumberTex = LoadTextureFilter(directory / "Assets/ui/mult_number.png");
    odMultShader = LoadShader(nullptr, "Assets/ui/odmult.fs");
    multNumberShader = LoadShader(nullptr, "Assets/ui/multnumber.fs");
    odFrame.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = odMultFrame;
    odFrame.materials[0].maps[MATERIAL_MAP_ALBEDO].color = player::accentColor;
    odBar.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = odMultFrame;
    odBar.materials[0].maps[MATERIAL_MAP_ALBEDO].color = player::accentColor;
    multFrame.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = odMultFrame;
    multFrame.materials[0].maps[MATERIAL_MAP_ALBEDO].color = player::accentColor;
    multBar.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = odMultFrame;
    multBar.materials[0].maps[MATERIAL_MAP_ALBEDO].color = player::accentColor;
    multCtr3.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = odMultFrame;
    multCtr3.materials[0].maps[MATERIAL_MAP_ALBEDO].color = player::accentColor;
    multCtr5.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = odMultFrame;
    multCtr5.materials[0].maps[MATERIAL_MAP_ALBEDO].color = player::accentColor;
    odBar.materials[0].maps[MATERIAL_MAP_EMISSION].texture = odMultFill;
    multBar.materials[0].maps[MATERIAL_MAP_EMISSION].texture = odMultFill;
    multCtr3.materials[0].maps[MATERIAL_MAP_EMISSION].texture = odMultFill;
    multCtr5.materials[0].maps[MATERIAL_MAP_EMISSION].texture = odMultFill;
    odBar.materials[0].shader = odMultShader;
    multBar.materials[0].shader = odMultShader;
    multCtr3.materials[0].shader = odMultShader;
    multCtr5.materials[0].shader = odMultShader;
    odLoc = GetShaderLocation(odMultShader, "overdrive");
    comboCounterLoc = GetShaderLocation(odMultShader, "comboCounter");
    multLoc = GetShaderLocation(odMultShader, "multBar");
    isBassOrVocalLoc = GetShaderLocation(odMultShader, "isBassOrVocal");
    odMultShader.locs[SHADER_LOC_MAP_EMISSION] = GetShaderLocation(odMultShader, "fillTex");

    multNumber.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = multNumberTex;
    multNumber.materials[0].shader = multNumberShader;
    uvOffsetXLoc = GetShaderLocation(multNumberShader, "uvOffsetX");
    uvOffsetYLoc = GetShaderLocation(multNumberShader, "uvOffsetY");

    expertHighwaySides = LoadModel(((directory / "Assets/highway/sides.obj").string().c_str()));
    expertHighway = LoadModel((directory / "Assets/highway/expert.obj").string().c_str());
    emhHighwaySides = LoadModel((directory / "Assets/highway/sides_emh.obj").string().c_str());
    emhHighway = LoadModel((directory / "Assets/highway/emh.obj").string().c_str());
    odHighwayEMH = LoadModel((directory / "Assets/highway/emh.obj").string().c_str());
    odHighwayX = LoadModel((directory / "Assets/highway/expert.obj").string().c_str());
    highwayTexture = LoadTextureFilter(directory / "Assets/highway/highway_new.png");
    highwayTextureOD = LoadTextureFilter(directory / "Assets/highway/highway_od.png");
    highwaySidesTexture = LoadTextureFilter(directory/"Assets/highway/highwaysides_new.png");
    odHighwayX.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = highwayTextureOD;
    odHighwayEMH.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = highwayTextureOD;
    odHighwayX.materials[0].maps[MATERIAL_MAP_ALBEDO].color = player::overdriveColor;
    odHighwayEMH.materials[0].maps[MATERIAL_MAP_ALBEDO].color = player::overdriveColor;
    expertHighwaySides.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = highwaySidesTexture;
    expertHighwaySides.materials[0].maps[MATERIAL_MAP_ALBEDO].color = player::accentColor;
    expertHighway.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = highwayTexture;
    expertHighway.materials[0].maps[MATERIAL_MAP_ALBEDO].color = LIGHTGRAY;
    emhHighwaySides.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = highwaySidesTexture;
    emhHighwaySides.materials[0].maps[MATERIAL_MAP_ALBEDO].color = player::accentColor;
    emhHighway.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = highwayTexture;
    emhHighway.materials[0].maps[MATERIAL_MAP_ALBEDO].color = LIGHTGRAY;
    noteModel = LoadModel((directory / "Assets/notes/note.obj").string().c_str());
    noteTexture = LoadTextureFilter(directory / "Assets/notes/note.png");
    emitTexture = LoadTextureFilter(directory / "Assets/notes/note_e_new.png");
    noteModel.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = noteTexture;
    noteModel.materials[0].maps[MATERIAL_MAP_ALBEDO].color = player::accentColor;
    noteModel.materials[0].maps[MATERIAL_MAP_EMISSION].texture = emitTexture;
    noteModel.materials[0].maps[MATERIAL_MAP_EMISSION].color = WHITE;
    noteModel.materials[0].maps[MATERIAL_MAP_EMISSION].value = 1;
    noteModelOD = LoadModel((directory / "Assets/notes/note.obj").string().c_str());
    noteTextureOD = LoadTextureFilter(directory / "Assets/notes/note.png");
    emitTextureOD = LoadTextureFilter(directory / "Assets/notes/note_e_new.png");
    noteModelOD.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = noteTextureOD;
    noteModelOD.materials[0].maps[MATERIAL_MAP_ALBEDO].color = WHITE;
    noteModelOD.materials[0].maps[MATERIAL_MAP_EMISSION].texture = emitTextureOD;
    noteModelOD.materials[0].maps[MATERIAL_MAP_EMISSION].color = WHITE;
    liftModel = LoadModel((directory / "Assets/notes/lift.obj").string().c_str());
    liftModel.materials[0].maps[MATERIAL_MAP_ALBEDO].color = player::accentColor;
    liftModelOD = LoadModel((directory / "Assets/notes/lift.obj").string().c_str());
    liftModelOD.materials[0].maps[MATERIAL_MAP_ALBEDO].color = WHITE;

    icon = LoadImage((directory / "Assets/encore_favicon-NEW.png").string().c_str());
    encoreWhiteLogo = LoadTextureFilter((directory / "Assets/encore-white.png"));
    songBackground = LoadTextureFilter((directory / "Assets/background.png"));

    redHatDisplayItalic = LoadFontEx((directory/"Assets/fonts/RedHatDisplay-BlackItalic.ttf").string().c_str(), 48,nullptr,0);
    SetTextureFilter(redHatDisplayItalic.texture, TEXTURE_FILTER_TRILINEAR);
    redHatDisplayLarge = LoadFontEx((directory/"Assets/fonts/RedHatDisplay-Black.ttf").string().c_str(), 128,nullptr,0);
    SetTextureFilter(redHatDisplayLarge.texture, TEXTURE_FILTER_TRILINEAR);
    rubik = LoadFontEx((directory / "Assets/fonts/Rubik-Regular.ttf").string().c_str(), 100, nullptr, 0);
    SetTextureFilter(rubik.texture, TEXTURE_FILTER_TRILINEAR);
    rubik32 = LoadFontEx((directory / "Assets/fonts/Rubik-Regular.ttf").string().c_str(), 32, nullptr, 0);
    SetTextureFilter(rubik32.texture, TEXTURE_FILTER_TRILINEAR);
    rubikBoldItalic32 = LoadFontEx((directory / "Assets/fonts/Rubik-BoldItalic.ttf").string().c_str(), 40, nullptr, 0);
    SetTextureFilter(rubikBoldItalic32.texture, TEXTURE_FILTER_TRILINEAR);
    rubikBold32 = LoadFontEx((directory / "Assets/fonts/Rubik-Bold.ttf").string().c_str(), 40, nullptr, 0);
    SetTextureFilter(rubikBold32.texture, TEXTURE_FILTER_TRILINEAR);
    //clapOD = LoadSound((directory / "Assets/highway/clap.ogg").string().c_str());
    //SetSoundVolume(clapOD, 0.375);

    discord = LoadTextureFilter(directory/"Assets/ui/discord-mark-white.png");
    github = LoadTextureFilter(directory/"Assets/ui/github-mark-white.png");
}