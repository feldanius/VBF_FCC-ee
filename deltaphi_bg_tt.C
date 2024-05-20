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
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_002305720.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_040770007.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_061671341.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_109801805.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_147909069.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_176750629.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_186308065.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_030697089.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_041382953.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_069529080.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_112284451.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_160967503.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_179017298.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_188114698.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_034090110.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_041623160.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_082237208.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_132342737.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_174977492.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_179183191.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_197112999.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_036581856.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_057484114.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_095701099.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_144749341.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_175335143.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_183045919.root"
    };

// Prototipo de la función de procesamiento
void processFile(const TString& inputFile, TH1F* hPhi, TH1F* hDeltaPhi);

int deltaphi_bg_tt() {
    TString outputFilePath = "deltaphi_bg_tt.root"; // Archivo de salida

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
