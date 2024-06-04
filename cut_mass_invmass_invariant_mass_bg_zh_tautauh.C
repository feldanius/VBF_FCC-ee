#include <iostream>
#include <vector>
#include <cmath>
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TLorentzVector.h"

using namespace std;

int cut_mass_invmass_invariant_mass_bg_zh_tautauh() {
    // Nombres de los archivos ROOT
    vector<string> filenames = {
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_tautauH_ecm365/events_015660911.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_tautauH_ecm365/events_058437289.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_tautauH_ecm365/events_094523955.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_tautauH_ecm365/events_160031364.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_tautauH_ecm365/events_175873169.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_tautauH_ecm365/events_192276123.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_tautauH_ecm365/events_043999218.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_tautauH_ecm365/events_090181769.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_tautauH_ecm365/events_116046380.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_tautauH_ecm365/events_162671919.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_tautauH_ecm365/events_186940475.root"
};

   // Crear un histograma para la masa invariante
    TH1F* hist_invariant_mass = new TH1F("hist_invariant_mass", "Masa invariante de los jets", 100, 0, 400);

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
        vector<float> jet_mass(2); // Agregar vector para la masa de los jets

        // Conectar las variables del árbol con las variables locales
        tree->SetBranchAddress("Jet.energy", &jet_energy[0]);
        tree->SetBranchAddress("Jet.momentum.x", &jet_px[0]);
        tree->SetBranchAddress("Jet.momentum.y", &jet_py[0]);
        tree->SetBranchAddress("Jet.momentum.z", &jet_pz[0]);
        tree->SetBranchAddress("Jet.mass", &jet_mass[0]); // Conectar la masa de los jets

        // Iterar sobre los eventos
        for (Long64_t i = 0; i < tree->GetEntries(); ++i) {
            tree->GetEntry(i);

            // Crear los vectores Lorentz de los jets
            vector<TLorentzVector> jets;

            for (int j = 0; j < 2; ++j) {
                // Aplicar el corte en la masa de los jets
                if (jet_mass[j] > 20.0) {
                    TLorentzVector jet;
                    jet.SetPxPyPzE(jet_px[j], jet_py[j], jet_pz[j], jet_energy[j]);
                    jets.push_back(jet);
                }
            }

            // Verificar que haya al menos dos jets
            if (jets.size() < 2) continue;

            // Calcular la masa invariante de los dos jets
            TLorentzVector dijet = jets[0] + jets[1];// Crear un histograma para la masa invariante
    TH1F* hist_invariant_mass = new TH1F("hist_invariant_mass", "Masa invariante de los jets", 100, 0, 400);

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
        vector<float> jet_mass(2); // Agregar vector para la masa de los jets

        // Conectar las variables del árbol con las variables locales
        tree->SetBranchAddress("Jet.energy", &jet_energy[0]);
        tree->SetBranchAddress("Jet.momentum.x", &jet_px[0]);
        tree->SetBranchAddress("Jet.momentum.y", &jet_py[0]);
        tree->SetBranchAddress("Jet.momentum.z", &jet_pz[0]);
        tree->SetBranchAddress("Jet.mass", &jet_mass[0]); // Conectar la masa de los jets

        // Iterar sobre los eventos
        for (Long64_t i = 0; i < tree->GetEntries(); ++i) {
            tree->GetEntry(i);

            // Crear los vectores Lorentz de los jets
            vector<TLorentzVector> jets;

            for (int j = 0; j < 2; ++j) {
                // Aplicar el corte en la masa de los jets
                if (jet_mass[j] > 20.0) {
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
            if (fabs(invariant_mass - mH) < 30.0) { // Invertir la condición
                // Llenar el histograma con la masa invariante
                hist_invariant_mass->Fill(invariant_mass);
            }
        }

        // Cerrar el archivo ROOT
        file->Close();
    }
            float invariant_mass = dijet.M();

            // Verificar el corte de la masa invariante
            const float mH = 125.0;
            if (fabs(invariant_mass - mH) < 30.0) { // Invertir la condición
                // Llenar el histograma con la masa invariante
                hist_invariant_mass->Fill(invariant_mass);
            }
        }

        // Cerrar el archivo ROOT
        file->Close();
    }

    // Guardar el histograma en un archivo ROOT
    TFile* output_file = TFile::Open("cut_mass_invmass_invariant_mass_jets_histogram_bg_zh_tautauh.root", "RECREATE");
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
