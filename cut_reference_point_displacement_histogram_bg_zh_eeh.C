#include <iostream>
#include <vector>
#include <cmath>
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TLorentzVector.h"
#include "TMath.h"

using namespace std;

int cut_reference_point_displacement_histogram_bg_zh_eeh() {
    // Nombres de los archivos ROOT
    vector<string> filenames = {
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

    // Crear un histograma para el desplazamiento del punto de referencia
    TH1F* hist_displacement = new TH1F("hist_displacement", "Desplazamiento del punto de referencia", 50, 0, 0.015);

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
        float missingEnergy;

        // Conectar las variables del árbol con las variables locales
        tree->SetBranchAddress("Jet.momentum.x", &jet_px[0]);
        tree->SetBranchAddress("Jet.momentum.y", &jet_py[0]);
        tree->SetBranchAddress("Jet.momentum.z", &jet_pz[0]);
        tree->SetBranchAddress("Jet.energy", &jet_energy[0]);
        tree->SetBranchAddress("Jet.mass", &jet_mass[0]);
        tree->SetBranchAddress("Jet.referencePoint.x", &jet_ref_x[0]);
        tree->SetBranchAddress("Jet.referencePoint.y", &jet_ref_y[0]);
        tree->SetBranchAddress("Jet.referencePoint.z", &jet_ref_z[0]);
        tree->SetBranchAddress("MissingET.energy", &missingEnergy);

        // Iterar sobre los eventos
        for (Long64_t i = 0; i < tree->GetEntries(); ++i) {
            tree->GetEntry(i);

            // Crear los vectores Lorentz de los jets
            vector<TLorentzVector> jets;
            vector<float> displacements;

            for (int j = 0; j < 2; ++j) {
                // Aplicar el corte en la masa de los jets
                if (jet_mass[j] < 60.0) {
                    TLorentzVector jet;
                    jet.SetPxPyPzE(jet_px[j], jet_py[j], jet_pz[j], jet_energy[j]);
                    jets.push_back(jet);

                    // Calcular el desplazamiento del punto de referencia
                    float displacement = sqrt(jet_ref_x[j] * jet_ref_x[j] + jet_ref_y[j] * jet_ref_y[j] + jet_ref_z[j] * jet_ref_z[j]);
                    displacements.push_back(displacement);
                }
            }

            // Verificar que haya al menos dos jets
            if (jets.size() < 2) continue;

            // Calcular la masa invariante de los dos jets
            TLorentzVector dijet = jets[0] + jets[1];
            float invariant_mass = dijet.M();

            // Calcular los ángulos azimutales (phi) de los dos jets
            float phi1 = TMath::ATan2(jets[0].Py(), jets[0].Px());
            float phi2 = TMath::ATan2(jets[1].Py(), jets[1].Px());

            // Calcular delta phi
            float deltaPhi = phi1 - phi2;
            if (deltaPhi > TMath::Pi()) {
                deltaPhi -= 2 * TMath::Pi();
            } else if (deltaPhi < -TMath::Pi()) {
                deltaPhi += 2 * TMath::Pi();
            }

            // Verificar el corte en delta phi
            if (deltaPhi < -0.83 * TMath::Pi() || deltaPhi > 0.83 * TMath::Pi()) continue;

            // Verificar el corte de la masa invariante
            const float mH = 125.0;
            if (fabs(invariant_mass - mH) < 30.0) {
                // Aplicar el corte adicional en el MET
                if (missingEnergy > 10.0 && missingEnergy < 150.0) {
                    // Llenar el histograma con el desplazamiento del punto de referencia de los dos leading jets
                    hist_displacement->Fill(displacements[0]);
                    hist_displacement->Fill(displacements[1]);
                }
            }
        }

        // Cerrar el archivo ROOT
        file->Close();
    }

    // Guardar el histograma en un archivo ROOT
    TFile* output_file = TFile::Open("cut_reference_point_displacement_histogram_bg_zh_eeh.root", "RECREATE");
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
