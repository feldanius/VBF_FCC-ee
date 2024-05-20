#include <iostream>
#include <vector>
#include <TString.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TMath.h>
#include <edm4hep/ReconstructedParticleData.h>

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
void processFile(const TString& inputFile, const TString& inputDir, TH1F* hPhi, TH1F* hDeltaPhi);

int deltaphi_signal() {
    TString outputFilePath = "output_histograms.root"; // Archivo de salida
// Crear histogramas
    TH1F* hPhi = new TH1F("hPhi", "Phi of Leading Jets;Phi (rad);Events", 50, -TMath::Pi(), TMath::Pi());
    TH1F* hDeltaPhi = new TH1F("hDeltaPhi", "Delta Phi of Leading Jets;Delta Phi (rad);Events", 50, -TMath::Pi(), TMath::Pi());

    // Procesar cada archivo
    for (const auto& inputFile : inputFileList) {
        processFile(inputFile, inputDirectory, hPhi, hDeltaPhi);
    }

    // Guardar histogramas en archivo de salida
    TFile outputFile(outputFilePath, "RECREATE");
    hPhi->Write();
    hDeltaPhi->Write();
    outputFile.Close();

    std::cout << "Histogramas guardados en " << outputFilePath << std::endl;
    delete hPhi; // Liberar memoria
    delete hDeltaPhi; // Liberar memoria
    return 0;
}

void processFile(const TString& inputFile, const TString& inputDir, TH1F* hPhi, TH1F* hDeltaPhi) {
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
    std::vector<edm4hep::ReconstructedParticleData>* jets = nullptr;

    // Set branch address
    tree->SetBranchAddress("Jet", &jets);

    // Loop sobre los eventos
    Long64_t nEntries = tree->GetEntries();
    for (Long64_t i = 0; i < nEntries; ++i) {
        tree->GetEntry(i);

        // Verificar que haya al menos dos jets
        if (jets->size() < 2) continue;

// Encontrar los leading jets (mayor energía)
        size_t leadingIndex1 = 0;
        size_t leadingIndex2 = 1;
        if ((*jets)[1].energy > (*jets)[0].energy) {
            leadingIndex1 = 1;
            leadingIndex2 = 0;
        }

	for (size_t j = 2; j < jets->size(); ++j) {
            if ((*jets)[j].energy > (*jets)[leadingIndex1].energy) {
                leadingIndex2 = leadingIndex1;
                leadingIndex1 = j;
            } else if ((*jets)[j].energy > (*jets)[leadingIndex2].energy) {
                leadingIndex2 = j;
            }
	}

	// Calcular phi para los leading jets
        float phi1 = TMath::ATan2((*jets)[leadingIndex1].momentum.y, (*jets)[leadingIndex1].momentum.x);
        float phi2 = TMath::ATan2((*jets)[leadingIndex2].momentum.y, (*jets)[leadingIndex2].momentum.x);

        // Llenar el histograma de phi
        hPhi->Fill(phi1);
        hPhi->Fill(phi2);
// Calcular phi para los leading jets
        float phi1 = TMath::ATan2((*jets)[leadingIndex1].momentum.y, (*jets)[leadingIndex1].momentum.x);
        float phi2 = TMath::ATan2((*jets)[leadingIndex2].momentum.y, (*jets)[leadingIndex2].momentum.x);

        // Llenar el histograma de phi
        hPhi->Fill(phi1);
        hPhi->Fill(phi2);

        // Calcular delta phi
        float deltaPhi = phi1 - phi2;
        if (deltaPhi > TMath::Pi()) {
            deltaPhi -= 2 * TMath::Pi();
        } else if (deltaPhi < -TMath::Pi()) {
            deltaPhi += 2 * TMath::Pi();
        }

	// Llenar el histograma de delta phi
        hDeltaPhi->Fill(deltaPhi);
    }

    // Cerrar el archivo de entrada
    inputFileRoot->Close();
}

