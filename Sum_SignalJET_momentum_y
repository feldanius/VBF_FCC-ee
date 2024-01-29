#include <iostream>
#include <TFile.h>
#include <TH1F.h>

int Sum_SignalJET_momentum_y() {
    const char* fileNames[] = {
        "SignalJET_momentum_y_events_019839222.root",
        "SignalJET_momentum_y_events_027985022.root",
        "SignalJET_momentum_y_events_067618566.root",
        "SignalJET_momentum_y_events_075207014.root",
        "SignalJET_momentum_y_events_088898158.root",
        "SignalJET_momentum_y_events_090014287.root",
        "SignalJET_momentum_y_events_129556080.root",
        "SignalJET_momentum_y_events_138935081.root",
        "SignalJET_momentum_y_events_176415634.root",
        "SignalJET_momentum_y_events_177743949.root",
        "SignalJET_momentum_y_events_178769856.root",
        "SignalJET_momentum_y_events_192707663.root"
    };

    // Variables para almacenar las secciones transversales y las luminosidades.
    Double_t crossSection = 0.05394;  // en pb
    Double_t luminosity = 1.5e-6;  // 1.5 ab^-1 expresado en pb^-1

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
            hist->Scale(crossSection * luminosity / hist->GetEntries());  // Normalización por sección transversal y luminosidad.

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
        const char* outputFileName = "Sum_SignalJET_momentum_y_histogram.root";
        TFile outputFileObj(outputFileName, "RECREATE");
        cumulativeHist->Write();
        outputFileObj.Close();

        std::cout << "Histograma normalizado guardado en " << outputFileName << std::endl;

        delete cumulativeHist;  // Libera la memoria del histograma acumulativo.
    }

    return 0;
}

int main() {
    Sum_SignalJET_momentum_y();  // Llamada a la función principal.

    return 0;
}
