#include <iostream>
#include <vector>
#include <cmath>
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"

using namespace std;

int reference_point_displacement_histogram_signal() {
    // Nombres de los archivos ROOT
    vector<string> filenames = {
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_008995949.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_034459462.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_067618566.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_088898158.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_107858353.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_158628525.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_177743949.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_192707663.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_019839222.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_061640142.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_071153275.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_090014287.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_129556080.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_174244458.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_178769856.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_027985022.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_065244791.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_075207014.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_090844778.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_138935081.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_176415634.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_180776309.root"
    };

    // Crear un histograma para el desplazamiento del punto de referencia
    TH1F* hist_displacement = new TH1F("hist_displacement", "Desplazamiento del punto de referencia", 100, 0, 10);

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
        vector<float> jet_px(2);
        vector<float> jet_py(2);
        vector<float> jet_pz(2);
        vector<float> jet_energy(2);
        vector<float> jet_mass(2);
        vector<float> jet_ref_x(2);
        vector<float> jet_ref_y(2);
        vector<float> jet_ref_z(2);

        // Conectar las variables del árbol con las variables locales
        tree->SetBranchAddress("Jet.momentum.x", &jet_px[0]);
        tree->SetBranchAddress("Jet.momentum.y", &jet_py[0]);
        tree->SetBranchAddress("Jet.momentum.z", &jet_pz[0]);
        tree->SetBranchAddress("Jet.energy", &jet_energy[0]);
        tree->SetBranchAddress("Jet.mass", &jet_mass[0]);
        tree->SetBranchAddress("Jet.referencePoint.x", &jet_ref_x[0]);
        tree->SetBranchAddress("Jet.referencePoint.y", &jet_ref_y[0]);
        tree->SetBranchAddress("Jet.referencePoint.z", &jet_ref_z[0]);

        // Iterar sobre los eventos
        for (Long64_t i = 0; i < tree->GetEntries(); ++i) {
            tree->GetEntry(i);

            // Crear los vectores Lorentz de los jets
            vector<TLorentzVector> jets;
            vector<float> displacements;

            for (int j = 0; j < 2; ++j) {
                TLorentzVector jet;
                jet.SetPxPyPzE(jet_px[j], jet_py[j], jet_pz[j], jet_energy[j]);
                jets.push_back(jet);

                // Calcular el desplazamiento del punto de referencia
                float displacement = sqrt(jet_ref_x[j] * jet_ref_x[j] + jet_ref_y[j] * jet_ref_y[j] + jet_ref_z[j] * jet_ref_z[j]);
                displacements.push_back(displacement);
            }

            // Si no hay dos jets, continuar con el siguiente evento
            if (jets.size() < 2) continue;

            // Llenar el histograma con el desplazamiento del punto de referencia de los dos leading jets
            hist_displacement->Fill(displacements[0]);
            hist_displacement->Fill(displacements[1]);
        }

        // Cerrar el archivo ROOT
        file->Close();
    }

    // Guardar el histograma en un archivo ROOT
    TFile* output_file = TFile::Open("reference_point_displacement_histogram_signal.root", "RECREATE");
    if (output_file) {
        hist_displacement->Write();
        output_file->Close();
    } else {
        cerr << "Error al abrir el archivo de salida" << endl;
    }

    // Limpiar la memoria
    delete hist_displacement;

    return 0;
}
