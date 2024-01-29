#include <iostream>
#include <vector>
#include <TString.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>

void processFile(const TString& inputFile, const TString& inputDir);

int MET_Signal_momentum_x() {
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

  for (const auto& inputFile : inputFileList) {
    processFile(inputFile, inputDirectory);
  }

  return 0;
}

void processFile(const TString& inputFile, const TString& inputDir) {
  // Construir la ruta completa del archivo de entrada
  TString inputFilePath = inputDir + inputFile;

  // Abrir el archivo de entrada
  TFile* inputFileRoot = TFile::Open(inputFilePath);

  // Verificar si el archivo se abrió correctamente
  if (!inputFileRoot || inputFileRoot->IsZombie()) {
    std::cerr << "Error abriendo el archivo: " << inputFilePath << std::endl;
    return 0;
  }

  // Obtener el árbol del archivo
  TTree* tree = (TTree*)inputFileRoot->Get("events");

  // Verificar si el árbol se obtuvo correctamente
  if (!tree) {
    std::cerr << "Error obteniendo el árbol 'events' del archivo: " << inputFilePath << std::endl;
    inputFileRoot->Close();
    return 0;
  }

// Crear un histograma y llenarlo con la información deseada
  TH1F* histo = new TH1F("MET", "MET", 100, 0, 500);
  tree->Draw("MissingET.momentum.x>>MET");

  // Hacer una copia de inputFile y quitar la extensión
  TString inputFileCopy = inputFile;
  TString inputFileNameWithoutExt = inputFileCopy.ReplaceAll(".root", "");

  // Construir el nombre del archivo de salida
  TString outputFileName = "SignalMET_momentum_x_" + inputFileNameWithoutExt + ".root";

  // Crear el archivo de salida y escribir el histograma
  TFile* outputFile = new TFile(outputFileName, "recreate");
  histo->Write();
  outputFile->Close();

  // Limpiar la memoria
  delete histo;
  delete inputFileRoot;

  std::cout << "Procesado correctamente: " << inputFilePath << std::endl;
        return 0;
}

