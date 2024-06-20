#include <iostream>
#include <TFile.h>
#include <TH1F.h>

int Sum_BackTTJET_mass() {
    const char* fileNames[] = {
"JET_BackTT_mass_events_002305720.root",
"JET_BackTT_mass_events_040770007.root",
"JET_BackTT_mass_events_061671341.root",
"JET_BackTT_mass_events_109801805.root",
"JET_BackTT_mass_events_147909069.root",
"JET_BackTT_mass_events_176750629.root",
"JET_BackTT_mass_events_186308065.root",
"JET_BackTT_mass_events_030697089.root",
"JET_BackTT_mass_events_041382953.root",
"JET_BackTT_mass_events_069529080.root",
"JET_BackTT_mass_events_112284451.root",
"JET_BackTT_mass_events_160967503.root",
"JET_BackTT_mass_events_179017298.root",
"JET_BackTT_mass_events_188114698.root",
"JET_BackTT_mass_events_034090110.root",
"JET_BackTT_mass_events_041623160.root",
"JET_BackTT_mass_events_082237208.root",
"JET_BackTT_mass_events_132342737.root",
"JET_BackTT_mass_events_174977492.root",
"JET_BackTT_mass_events_179183191.root",
"JET_BackTT_mass_events_197112999.root",
"JET_BackTT_mass_events_036581856.root",
"JET_BackTT_mass_events_057484114.root",
"JET_BackTT_mass_events_095701099.root",
"JET_BackTT_mass_events_144749341.root",
"JET_BackTT_mass_events_175335143.root",
"JET_BackTT_mass_events_183045919.root"
    };

    // Variables para almacenar las secciones transversales y las luminosidades.
    Double_t crossSection = 0.8;  // en pb
    Double_t luminosity = 2.4e6;  // 2.4 ab^-1 expresado en pb^-1

    // Crea un histograma acumulativo para almacenar la suma de los histogramas normalizados.
    TH1F* cumulativeHist = nullptr;

    for (int i = 0; i < sizeof(fileNames) / sizeof(fileNames[0]); ++i) {
        // Abre el archivo ROOT.
        TFile file(fileNames[i]);

        // Comprueba si se abrió correctamente el archivo.
        if (file.IsZombie()) {
            std::cerr << "Error: No se pudo abrir el archivo " << fileNames[i] << std::endl;
            continue;
        }

        // Intenta obtener el histograma directamente del archivo.
        TH1F* hist = dynamic_cast<TH1F*>(file.Get("JET"));

        // Normaliza el histograma.
        if (hist) {
            hist->Scale(crossSection * luminosity );  // Normalización por sección transversal y luminosidad.

            // Si es el primer archivo, crea el histograma acumulativo.
            if (!cumulativeHist) {
                cumulativeHist = new TH1F(*hist);
                cumulativeHist->SetDirectory(nullptr);  // Desvincula el histograma del archivo.
            } else {
                cumulativeHist->Add(hist);  // Agrega el histograma normalizado al histograma acumulativo.
            }
        } else {
            std::cerr << "Error: No se pudo obtener el histograma del archivo " << fileNames[i] << std::endl;
        }
    }

    if (cumulativeHist) {
        // Guarda el histograma acumulativo normalizado en un nuevo archivo.
        const char* outputFileName = "BackTTJET_mass_histogram.root";
        TFile outputFileObj(outputFileName, "RECREATE");
        cumulativeHist->Write();
        outputFileObj.Close();

        std::cout << "Histograma normalizado guardado en " << outputFileName << std::endl;

        delete cumulativeHist;  // Libera la memoria del histograma acumulativo.
    }

    return 0;
}

int main() {
    Sum_BackTTJET_mass();  // Llamada a la función principal.

    return 0;
}
