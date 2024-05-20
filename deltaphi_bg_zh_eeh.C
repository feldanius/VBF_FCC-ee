#include <iostream>
#include <vector>
#include <TString.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TMath.h>
#include <edm4hep/ReconstructedParticleData.h>

using namespace std;
// Lista de archivos con rutas completas
std::vector<std::string> filenames = {
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_eeH_ecm365/events_018107429.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_eeH_ecm365/events_104473316.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_eeH_ecm365/events_117039771.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_eeH_ecm365/events_130128294.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_eeH_ecm365/events_173768499.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_eeH_ecm365/events_047118042.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_eeH_ecm365/events_107849662.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_eeH_ecm365/events_118636096.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_eeH_ecm365/events_153113508.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_eeH_ecm365/events_182514790.root"

    };


// Prototipo de la función de procesamiento
void processFile(const TString& inputFile, TH1F* hPhi, TH1F* hDeltaPhi);

int deltaphi_bg_zh_eeh() {
    TString outputFilePath = "deltaphi_bg_zh_eeh.root"; // Archivo de salida

    // Crear histogramas
    TH1F* hPhi = new TH1F("hPhi", "Phi of Leading Jets;Phi (rad);Events", 50, -TMath::Pi(), TMath::Pi());
    TH1F* hDeltaPhi = new TH1F("hDeltaPhi", "Delta Phi of Leading Jets;Delta Phi (rad);Events", 50, -TMath::Pi(), TMath::Pi());

    // Procesar cada archivo
    for (const auto& inputFile : filenames) {
        processFile(inputFile.c_str(), hPhi, hDeltaPhi);
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

void processFile(const TString& inputFile, TH1F* hPhi, TH1F* hDeltaPhi) {
    // Abrir el archivo de entrada
    TFile* inputFileRoot = TFile::Open(inputFile);

    // Verificar si el archivo se abrió correctamente
    if (!inputFileRoot || inputFileRoot->IsZombie()) {
        std::cerr << "Error abriendo el archivo: " << inputFile << std::endl;
        return;
    }

    // Obtener el árbol del archivo
    TTree* tree = (TTree*)inputFileRoot->Get("events");

    // Verificar si el árbol se obtuvo correctamente
    if (!tree) {
        std::cerr << "Error obteniendo el árbol 'events' del archivo: " << inputFile << std::endl;
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
