export default class SCR {
    constructor(acessos, quadros) {
        this.lista = [];
        this.tamanhoMaximo = quadros;
        this.qtdPageFault = 0;
        this.acessos = acessos;
        this.ponteiro = 0;
    }

    acessarPaginas() {
        this.acessos.forEach(e => {
            this.procurarPagina(e);
        });
        return this.qtdPageFault;
    }

    procurarPagina(pag) {
        let encontrou = false;

        for (let i = 0; i < this.lista.length; i++) {
            if (this.lista[i].pag === pag) {
                this.lista[i].ref = 1;
                encontrou = true;
                break;
            }
        }

        if (!encontrou) {
            
            this.qtdPageFault++;
            
            let substituiu = false;
            while(!substituiu) {
                if (this.lista[this.ponteiro] === undefined ||
                    this.lista[this.ponteiro].ref === 0) {

                    this.lista[this.ponteiro] = { "pag": pag, "ref": 0 };
                    this.ponteiro = (this.ponteiro + 1 + this.tamanhoMaximo) % this.tamanhoMaximo; 
                    substituiu = true;
                } else {
                    this.lista[this.ponteiro].ref = 0;
                    this.ponteiro = (this.ponteiro + 1 + this.tamanhoMaximo) % this.tamanhoMaximo;

                }
            }
        }
    }
}