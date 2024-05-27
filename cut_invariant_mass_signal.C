#include <iostream>
#include <vector>
#include <cmath>
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TLorentzVector.h"

using namespace std;

int cut_invariant_mass_signal() {
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
        vector<int> jet_tracks_begin(2);
        vector<int> jet_tracks_end(2);
        vector<float> jet_mass(2);
        vector<float> jet_goodnessOfPID(2);
        vector<float> jet_ref_x(2);
        vector<float> jet_ref_y(2);
        vector<float> jet_ref_z(2);
        vector<vector<float>> jet_covMatrix(2, vector<float>(10));

        // Conectar las variables del árbol con las variables locales
        tree->SetBranchAddress("Jet.energy", &jet_energy[0]);
        tree->SetBranchAddress("Jet.momentum.x", &jet_px[0]);
        tree->SetBranchAddress("Jet.momentum.y", &jet_py[0]);
        tree->SetBranchAddress("Jet.momentum.z", &jet_pz[0]);
        tree->SetBranchAddress("Jet.tracks_begin", &jet_tracks_begin[0]);
        tree->SetBranchAddress("Jet.tracks_end", &jet_tracks_end[0]);
        tree->SetBranchAddress("Jet.mass", &jet_mass[0]);
        tree->SetBranchAddress("Jet.goodnessOfPID", &jet_goodnessOfPID[0]);
        tree->SetBranchAddress("Jet.referencePoint.x", &jet_ref_x[0]);
        tree->SetBranchAddress("Jet.referencePoint.y", &jet_ref_y[0]);
        tree->SetBranchAddress("Jet.referencePoint.z", &jet_ref_z[0]);
        tree->SetBranchAddress("Jet.covMatrix", &jet_covMatrix[0][0]);

        // Iterar sobre los eventos
        for (Long64_t i = 0; i < tree->GetEntries(); ++i) {
            tree->GetEntry(i);

            // Crear los vectores Lorentz de los jets
            vector<TLorentzVector> jets;
            vector<int> btagged_jets;

            for (int j = 0; j < 2; ++j) {
                int num_tracks = jet_tracks_end[j] - jet_tracks_begin[j];
                float mass = jet_mass[j];
                float goodnessOfPID = jet_goodnessOfPID[j];
                float displacement = sqrt(jet_ref_x[j]*jet_ref_x[j] + jet_ref_y[j]*jet_ref_y[j] + jet_ref_z[j]*jet_ref_z[j]);

                // Evaluar la calidad de la medición (ejemplo: usar el primer elemento de la matriz de covarianza)
                float quality = jet_covMatrix[j][0];

                // Criterio de b-tagging: más de 2 tracks, masa mayor a un umbral, buena PID, desplazamiento significativo y buena calidad de medición
                if (num_tracks > 2 && mass > 5.0 && goodnessOfPID > 0.8 && displacement > 0.1 && quality < 1.0) {  // Ajustar los umbrales según sea necesario
                    TLorentzVector jet;
                    jet.SetPxPyPzE(jet_px[j], jet_py[j], jet_pz[j], jet_energy[j]);
                    jets.push_back(jet);
                    btagged_jets.push_back(j);
                }
            }

            // Si no hay dos jets b-tagged, continuar con el siguiente evento
            if (jets.size() < 2) continue;

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
    TFile* output_file = TFile::Open("cut_invariant_mass_jets_histogram_signal_400.root", "RECREATE");
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
