#include <iostream>
#include <vector>
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TLorentzVector.h"

using namespace std;
int invariant_mass_BackTT() {
    // Nombres de los archivos ROOT
    vector<string> filenames = {
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/"

    };

    // Crear un histograma para la masa invariante
    TH1F* hist_invariant_mass = new TH1F("hist_invariant_mass", "Masa invariante de los jets", 100, 0, 200);

    // Iterar sobre los archivos
    for (const auto& filename : filenames) {
        // Abrir archivo ROOT
        TFile* file = TFile::Open(filename.c_str());
        if (!file) {
            cerr << "Error al abrir el archivo " << filename << endl;
            continue;
        }

        // Obtener el árbol de eventos
        TTree* tree = (TTree*)file->Get("events");
        if (!tree) {
            cerr << "No se pudo encontrar el árbol de eventos en " << filename << endl;
            file->Close();
            continue;
        }

        // Variables para almacenar la información de los jets
        vector<float> jet_energy(2);
        vector<float> jet_px(2);
        vector<float> jet_py(2);
        vector<float> jet_pz(2);

        // Conectar las variables del árbol con las variables locales
        tree->SetBranchAddress("Jet.energy", &jet_energy[0]);
        tree->SetBranchAddress("Jet.momentum.x", &jet_px[0]);
        tree->SetBranchAddress("Jet.momentum.y", &jet_py[0]);
        tree->SetBranchAddress("Jet.momentum.z", &jet_pz[0]);

        // Iterar sobre los eventos
        for (Long64_t i = 0; i < tree->GetEntries(); ++i) {
            tree->GetEntry(i);

            // Crear los vectores Lorentz de los jets
            vector<TLorentzVector> jets;
            for (int j = 0; j < 2; ++j) {
                TLorentzVector jet;
                jet.SetPxPyPzE(jet_px[j], jet_py[j], jet_pz[j], jet_energy[j]);
                jets.push_back(jet);
            }

            // Calcular la masa invariante
            TLorentzVector dijet = jets[0] + jets[1];
            float invariant_mass = dijet.M();

            // Llenar el histograma con la masa invariante
            hist_invariant_mass->Fill(invariant_mass);
        }

        // Cerrar el archivo ROOT
        file->Close();
    }

    // Guardar el histograma en un archivo ROOT
    TFile* output_file = TFile::Open("invariant_mass_jets_histogram_BackTT.root", "RECREATE");
    if (output_file) {
        hist_invariant_mass->Write();
        output_file->Close();
    } else {
        cerr << "Error al abrir el archivo de salida" << endl;
    }

    // Limpiar la memoria
    delete hist_invariant_mass;

    return 0;
}
