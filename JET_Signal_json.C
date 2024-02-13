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

int JET_Signal_json() {
    // Lista de archivos de entrada
    std::vector<TString> inputFileList = {
    "events_019839222.root",
    "events_067618566.root",
    "events_088898158.root",
    "events_129556080.root",
    "events_176415634.root",
    "events_178769856.root",
    "events_027985022.root",
    "events_075207014.root",
    "events_090014287.root",
    "events_138935081.root",
    "events_177743949.root",
    "events_192707663.root"
  };

//cout << "\t The folder you are trying to create already exists \n" << endl;

  // Directorio de salida
  TString inputDirectory = "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/";

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
        jsonData["OutputFile"] = "SignalJET_energy_" + inputFileNameWithoutExt + ".root";
        //jsonData["OutputFile"] = "SignalJET_mass_" + inputFileNameWithoutExt + ".root";
        //jsonData["OutputFile"] = "SignalJET_momentum_x_" + inputFileNameWithoutExt + ".root";
        //jsonData["OutputFile"] = "SignalJET_momentum_y_" + inputFileNameWithoutExt + ".root";
        //jsonData["OutputFile"] = "SignalJET_momentum_z_" + inputFileNameWithoutExt + ".root";
        
        // Agregar este JSON al objeto combinado
        combinedJsonData.push_back(jsonData);
    }

    // Escribir el archivo JSON
    std::ofstream jsonOutput("SignalJET_energy.json");
    //std::ofstream jsonOutput("SignalJET_mass.json");
    //std::ofstream jsonOutput("SignalJET_momentum_x.json");
    //std::ofstream jsonOutput("SignalJET_momentum_y.json");
    //std::ofstream jsonOutput("SignalJET_momentum_z.json");
    jsonOutput << std::setw(4) << combinedJsonData;

    // Informar al usuario
    std::cout << "Archivo JSON generado." << std::endl;
}

