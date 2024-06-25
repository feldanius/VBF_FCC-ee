#include <iostream>
#include <vector>
#include <TString.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TMath.h>
#include <cmath>
#include <TLorentzVector.h>

using namespace std;

// Lista de archivos con rutas completas
std::vector<std::string> filenames = {
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_mumuH_ecm365/events_023261681.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_mumuH_ecm365/events_034927544.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_mumuH_ecm365/events_058572739.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_mumuH_ecm365/events_073291643.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_mumuH_ecm365/events_092281869.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_mumuH_ecm365/events_189404834.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_mumuH_ecm365/events_033570460.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_mumuH_ecm365/events_036028207.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_mumuH_ecm365/events_068513877.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_mumuH_ecm365/events_075232335.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_mumuH_ecm365/events_183713990.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_mumuH_ecm365/events_197337122.root"
    };


// Prototipo de la función de procesamiento
void processFile(const TString& inputFile, TH1F* hDeltaPhi);

int cut_deltaphi_bg_zh_mumuh() {
    TString outputFilePath = "cut_deltaphi_bg_zh_mumuh.root"; // Archivo de salida

    // Crear histograma
    TH1F* hDeltaPhi = new TH1F("hDeltaPhi", "Delta Phi of Leading Jets;Delta Phi (rad);Events", 50, -TMath::Pi(), TMath::Pi());

    // Procesar cada archivo
    for (const auto& inputFile : filenames) {
        processFile(inputFile.c_str(), hDeltaPhi);
    }

    // Guardar histograma en archivo de salida
    TFile outputFile(outputFilePath, "RECREATE");
    hDeltaPhi->Write();
    outputFile.Close();

    std::cout << "Histograma guardado en " << outputFilePath << std::endl;
    delete hDeltaPhi; // Liberar memoria
    return 0;
}

void processFile(const TString& inputFile, TH1F* hDeltaPhi) {
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
    std::vector<float> jet_mass(2);
    float missingEnergy;
    std::vector<float> jet_px(2);
    std::vector<float> jet_py(2);
    std::vector<float> jet_pz(2);
    std::vector<float> jet_energy(2);

    // Set branch address
    tree->SetBranchAddress("Jet.energy", &jet_energy[0]);
    tree->SetBranchAddress("Jet.momentum.x", &jet_px[0]);
    tree->SetBranchAddress("Jet.momentum.y", &jet_py[0]);
    tree->SetBranchAddress("Jet.momentum.z", &jet_pz[0]);
    tree->SetBranchAddress("Jet.mass", &jet_mass[0]); // Conectar la masa de los jets
    tree->SetBranchAddress("MissingET.energy", &missingEnergy);

    // Loop sobre los eventos
    Long64_t nEntries = tree->GetEntries();
    for (Long64_t i = 0; i < nEntries; ++i) {
        tree->GetEntry(i);

        vector<TLorentzVector> jets;

        for (int j = 0; j < 2; ++j) {
            // Aplicar el corte en la masa de los jets
            if (jet_mass[j] < 60.0) {
                TLorentzVector jet;
                jet.SetPxPyPzE(jet_px[j], jet_py[j], jet_pz[j], jet_energy[j]);
                jets.push_back(jet);
            }
        }

        // Verificar que haya al menos dos jets
        if (jets.size() < 2) continue;

        // Calcular la masa invariante de los dos jets
        TLorentzVector dijet = jets[0] + jets[1];
        float invariant_mass = dijet.M();

        // Verificar el corte de la masa invariante
        const float mH = 125.0;
        if (fabs(invariant_mass - mH) < 30.0) {
            // Aplicar el corte adicional en el MET
            if (missingEnergy >= 10.0 && missingEnergy <= 150.0) {
                // Calcular delta phi
                float phi1 = jets[0].Phi();
                float phi2 = jets[1].Phi();
                float deltaPhi = phi1 - phi2;
                if (deltaPhi > TMath::Pi()) {
                    deltaPhi -= 2 * TMath::Pi();
                } else if (deltaPhi < -TMath::Pi()) {
                    deltaPhi += 2 * TMath::Pi();
                }

                // Llenar el histograma de delta phi
                hDeltaPhi->Fill(deltaPhi);
            }
        }
    }

    // Cerrar el archivo de entrada
    inputFileRoot->Close();
}
