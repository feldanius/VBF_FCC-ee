#include <iostream>
#include <vector>
#include <TString.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TMath.h>

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
    "events_192707663.root",
    "events_008995949.root",
    "events_061640142.root",
    "events_107858353.root",
    "events_174244458.root",
    "events_180776309.root",
    "events_065244791.root",
    "events_034459462.root",
    "events_071153275.root",
    "events_090844778.root",
    "events_158628525.root"
};

TString inputDirectory = "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/";

// Prototipo de la función de procesamiento
void processFile(const TString& inputFile, const TString& inputDir, TH1F* hist);

int deltaphi_signal() {
    TString outputFilePath = "output_delta_phi.root"; // Mover esta línea aquí para mayor claridad

    // Crear histograma para delta phi
    TH1F* hDeltaPhi = new TH1F("hDeltaPhi", "Delta Phi of Leading Jets;Delta Phi (rad);Events", 50, -TMath::Pi(), TMath::Pi());

    // Procesar cada archivo
    for (const auto& inputFile : inputFileList) {
        processFile(inputFile, inputDirectory, hDeltaPhi);
    }

    // Guardar histograma en archivo de salida
    TFile outputFile(outputFilePath, "RECREATE");
    hDeltaPhi->Write();
    outputFile.Close();

    std::cout << "Histograma guardado en " << outputFilePath << std::endl;
    delete hDeltaPhi; // Liberar memoria
    return 0;
}

void processFile(const TString& inputFile, const TString& inputDir, TH1F* hist) {
    // Construir la ruta completa del archivo de entrada
    TString inputFilePath = inputDir + inputFile;

    // Abrir el archivo de entrada
    TFile* inputFileRoot = TFile::Open(inputFilePath);

    // Verificar si el archivo se abrió correctamente
    if (!inputFileRoot || inputFileRoot->IsZombie()) {
        std::cerr << "Error abriendo el archivo: " << inputFilePath << std::endl;
        return;
    }

    // Obtener el árbol del archivo
    TTree* tree = (TTree*)inputFileRoot->Get("events");

    // Verificar si el árbol se obtuvo correctamente
    if (!tree) {
        std::cerr << "Error obteniendo el árbol 'events' del archivo: " << inputFilePath << std::endl;
        inputFileRoot->Close();
        return;
    }

    // Variables para almacenar datos del árbol
    std::vector<float>* px = 0;
    std::vector<float>* py = 0;
    std::vector<float>* energy = 0;

    // Set branch addresses
    tree->SetBranchAddress("Jet.momentum.x", &px);
    tree->SetBranchAddress("Jet.momentum.y", &py);
    tree->SetBranchAddress("Jet.energy", &energy);

    // Loop sobre los eventos
    Long64_t nEntries = tree->GetEntries();
    for (Long64_t i = 0; i < nEntries; ++i) {
        tree->GetEntry(i);

        // Verificar que haya al menos dos jets
        if (px->size() < 2 || py->size() < 2) continue;

        // Encontrar los leading jets (mayor energía)
        size_t leadingIndex1 = 0;
        size_t leadingIndex2 = 1;
        if ((*energy)[1] > (*energy)[0]) {
            leadingIndex1 = 1;
            leadingIndex2 = 0;
        }

        for (size_t j = 2; j < energy->size(); ++j) {
            if ((*energy)[j] > (*energy)[leadingIndex1]) {
                leadingIndex2 = leadingIndex1;
                leadingIndex1 = j;
            } else if ((*energy)[j] > (*energy)[leadingIndex2]) {
                leadingIndex2 = j;
            }
        }

        // Calcular phi para los leading jets
        float phi1 = TMath::ATan2((*py)[leadingIndex1], (*px)[leadingIndex1]);
        float phi2 = TMath::ATan2((*py)[leadingIndex2], (*px)[leadingIndex2]);

        // Calcular delta phi
        float deltaPhi = phi1 - phi2;
        if (deltaPhi > TMath::Pi()) {
            deltaPhi -= 2 * TMath::Pi();
        } else if (deltaPhi < -TMath::Pi()) {
            deltaPhi += 2 * TMath::Pi();
        }

        // Llenar el histograma
        hist->Fill(deltaPhi);
    }

    // Cerrar el archivo de entrada
    inputFileRoot->Close();
}
