#include <iostream>
#include <vector>
#include <TString.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

void processFiles(const std::vector<TString>& inputFileList, const TString& inputDir);

int MET_BackWW_json() {
    // Lista de archivos de entrada
    std::vector<TString> inputFileList = {
    "events_000081890.root", "events_045401282.root", "events_077177641.root", "events_094831572.root",
    "events_124947653.root", "events_164771774.root", "events_001084100.root", "events_047601629.root",
    "events_077961119.root", "events_096182593.root", "events_125410393.root", "events_165573084.root",
    "events_001936135.root", "events_048519618.root", "events_079581581.root", "events_097812473.root",
    "events_125694683.root", "events_166404736.root", "events_003311959.root", "events_049205238.root",
    "events_079874852.root", "events_098861309.root", "events_126621262.root", "events_166556689.root",
    "events_008517319.root", "events_050743883.root", "events_080551146.root", "events_102710384.root",
    "events_126980955.root", "events_169254437.root", "events_009112042.root", "events_053823202.root",
    "events_081326715.root", "events_105118674.root", "events_128303671.root", "events_170034851.root",
    "events_009922998.root", "events_057309409.root", "events_083171779.root", "events_105861383.root",
    "events_131696833.root", "events_170853329.root", "events_014470540.root", "events_058259071.root",
    "events_083476787.root", "events_106404137.root", "events_131936722.root", "events_172262746.root",
    "events_021086660.root", "events_058821537.root", "events_086285467.root", "events_107743170.root",
    "events_132219478.root", "events_172839947.root", "events_025952229.root", "events_059805625.root",
    "events_086774567.root", "events_109538064.root", "events_133605307.root", "events_176643119.root",
    "events_026548305.root", "events_060795865.root", "events_087040405.root", "events_110263413.root",
    "events_137524898.root", "events_184083150.root", "events_027513730.root", "events_061978404.root",
    "events_087452123.root", "events_111995477.root", "events_137590494.root", "events_185820725.root",
    "events_028546045.root", "events_063772509.root", "events_088117927.root", "events_114994428.root",
    "events_142151386.root", "events_186294283.root", "events_030420744.root", "events_064075216.root",
    "events_089976236.root", "events_116804196.root", "events_142326431.root", "events_186696649.root",
    "events_031548033.root", "events_067382959.root", "events_090775421.root", "events_118835962.root",
    "events_143339192.root", "events_188767652.root", "events_032448280.root", "events_068617186.root",
    "events_091240706.root", "events_121819232.root", "events_143879209.root", "events_194083404.root",
    "events_036902764.root", "events_069328331.root", "events_092739974.root", "events_122228448.root",
    "events_144306993.root", "events_196309639.root", "events_042360866.root", "events_069637696.root",
    "events_093654693.root", "events_123849603.root", "events_149880888.root", "events_198386659.root",
    "events_043211856.root", "events_071710976.root", "events_093871872.root", "events_124008190.root",
    "events_150747171.root", "events_044550239.root", "events_071992535.root", "events_094227409.root",
    "events_124377335.root", "events_157525244.root"
  };

    // Directorio de entrada
    TString inputDirectory = "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_WW_ecm365/";

    processFiles(inputFileList, inputDirectory);

    return 0;
}

void processFiles(const std::vector<TString>& inputFileList, const TString& inputDir) {
    // Objeto para almacenar la información combinada de todos los archivos ROOT
    json combinedJsonData;

    // Procesar cada archivo ROOT
    for (const auto& inputFile : inputFileList) {
        // Construir la ruta completa del archivo de entrada
        TString inputFilePath = inputDir + inputFile;

        // Crear el JSON para este archivo ROOT
        json jsonData;
        jsonData["InputFile"] = inputFilePath.Data();
        TString inputFileNameWithoutExt = inputFile;
        inputFileNameWithoutExt.ReplaceAll(".root", "");
        jsonData["OutputFile"] = "BackWWMET_energy_" + inputFileNameWithoutExt + ".root";
        //jsonData["OutputFile"] = "BackWWMET_mass_" + inputFileNameWithoutExt + ".root";
        //jsonData["OutputFile"] = "BackWWMET_momentum_x_" + inputFileNameWithoutExt + ".root";
        //jsonData["OutputFile"] = "BackWWMET_momentum_y_" + inputFileNameWithoutExt + ".root";
        //jsonData["OutputFile"] = "BackWWMET_momentum_z_" + inputFileNameWithoutExt + ".root";
        
        // Agregar este JSON al objeto combinado
        combinedJsonData.push_back(jsonData);
    }

    // Escribir el archivo JSON
    std::ofstream jsonOutput("BackWWMET_energy.json");
    //std::ofstream jsonOutput("BackWWMET_mass.json");
    //std::ofstream jsonOutput("BackWWMET_momentum_x.json");
    //std::ofstream jsonOutput("BackWWMET_momentum_y.json");
    //std::ofstream jsonOutput("BackWWMET_momentum_z.json");
    jsonOutput << std::setw(4) << combinedJsonData;

    // Informar al usuario
    std::cout << "Archivo JSON generado." << std::endl;
}

