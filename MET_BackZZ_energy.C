#include <iostream>
#include <vector>
#include <TString.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>

void processFile(const TString& inputFile, const TString& inputDir);

int MET_BackZZ_energy() {
  // Lista de archivos de entrada
  std::vector<TString> inputFileList = {
    "events_001696302.root", "events_032633846.root", "events_053973825.root", "events_087994603.root",
    "events_115267766.root", "events_144026616.root", "events_158889908.root", "events_175951222.root",
    "events_003001058.root", "events_033322185.root", "events_056171721.root", "events_090238630.root",
    "events_115660713.root", "events_144320233.root", "events_159472455.root", "events_176338267.root",
    "events_004542872.root", "events_034365885.root", "events_056792216.root", "events_092851225.root",
    "events_116050595.root", "events_145545538.root", "events_159848992.root", "events_180144303.root",
    "events_008932909.root", "events_034529401.root", "events_060919902.root", "events_093762749.root",
    "events_121964585.root", "events_145856382.root", "events_160757782.root", "events_182425053.root",
    "events_014127399.root", "events_036305182.root", "events_062077114.root", "events_098295024.root",
    "events_125013562.root", "events_146587224.root", "events_162157559.root", "events_185580770.root",
    "events_014838097.root", "events_040468238.root", "events_062502766.root", "events_098351043.root",
    "events_125315792.root", "events_147318350.root", "events_162792908.root", "events_187308074.root",
    "events_019088425.root", "events_041749934.root", "events_062545514.root", "events_101754828.root",
    "events_126295024.root", "events_148119516.root", "events_163026739.root", "events_188706220.root",
    "events_020161630.root", "events_046453381.root", "events_067149354.root", "events_102206217.root",
    "events_129205309.root", "events_148401866.root", "events_164282910.root", "events_192439824.root",
    "events_024624496.root", "events_047210663.root", "events_067298136.root", "events_103732607.root",
    "events_130061441.root", "events_150419675.root", "events_166104738.root", "events_193415571.root",
    "events_024745237.root", "events_051420387.root", "events_068718613.root", "events_105307492.root",
    "events_133692815.root", "events_152659631.root", "events_167291958.root", "events_194417088.root",
    "events_027132528.root", "events_052214341.root", "events_071619177.root", "events_107050183.root",
    "events_135840565.root", "events_155577588.root", "events_168889214.root",
    "events_029574438.root", "events_052424361.root", "events_077020967.root", "events_109090276.root",
    "events_137736367.root", "events_155810265.root", "events_169971509.root",
    "events_030275741.root", "events_052657692.root", "events_078207694.root", "events_113083371.root",
    "events_138495552.root", "events_158107052.root", "events_170552925.root",
    "events_030710516.root", "events_053073147.root", "events_083349007.root", "events_113282591.root",
    "events_140935835.root", "events_158393095.root", "events_172299325.root",
    "events_031684841.root", "events_053697318.root", "events_084251123.root", "events_113574790.root",
    "events_140984869.root", "events_158654042.root", "events_175533196.root"
  };

//cout << "\t The folder you are trying to create already exists \n" << endl;

  // Directorio de salida
  TString inputDirectory = "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_ZZ_ecm365/";

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
  tree->Draw("MissingET.energy>>MET");

  // Hacer una copia de inputFile y quitar la extensión
  TString inputFileCopy = inputFile;
  TString inputFileNameWithoutExt = inputFileCopy.ReplaceAll(".root", "");

  // Construir el nombre del archivo de salida
  TString outputFileName = "BackZZMET_energy_" + inputFileNameWithoutExt + ".root";

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

