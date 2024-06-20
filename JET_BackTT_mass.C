#include <iostream>
#include <vector>
#include <TString.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>

void processFile(const TString& inputFile, const TString& inputDir);

int JET_BackTT_mass() {
  // Lista de archivos de entrada
  std::vector<TString> inputFileList = {
"events_002305720.root",
"events_040770007.root",
"events_061671341.root",
"events_109801805.root",
"events_147909069.root",
"events_176750629.root",
"events_186308065.root",
"events_030697089.root",
"events_041382953.root",
"events_069529080.root",
"events_112284451.root",
"events_160967503.root",
"events_179017298.root",
"events_188114698.root",
"events_034090110.root",
"events_041623160.root",
"events_082237208.root",
"events_132342737.root",
"events_174977492.root",
"events_179183191.root",
"events_197112999.root",
"events_036581856.root",
"events_057484114.root",
"events_095701099.root",
"events_144749341.root",
"events_175335143.root",
"events_183045919.root"
  };

//cout << "\t The folder you are trying to create already exists \n" << endl;

  // Directorio de salida
  TString inputDirectory = "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/";

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
  TH1F* histo = new TH1F("JET", "JET", 100, 0, 500);
  tree->Draw("Jet.mass>>JET");

  // Hacer una copia de inputFile y quitar la extensión
  TString inputFileCopy = inputFile;
  TString inputFileNameWithoutExt = inputFileCopy.ReplaceAll(".root", "");

  // Construir el nombre del archivo de salida
  TString outputFileName = "JET_BackTT_mass_" + inputFileNameWithoutExt + ".root";

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
