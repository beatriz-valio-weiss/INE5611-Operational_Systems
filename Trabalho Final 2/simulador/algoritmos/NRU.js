export default class NRU {
    constructor(acessos, quadros) {
        this.mutex = 0;
        this.lista = [];
        this.tamanhoMaximo = quadros;
        this.qtdPageFault = 0;
        this.acessos = acessos;

        this.interval = setInterval(() => {
            if(this.mutex == 0) {
                this.mutex = 1;
                this.lista.forEach(q => {
                    if(q !== undefined) {
                        q.ref = 0;
                    }
                })
                this.mutex = 0;
            }
        }, 100);
    }

    acessarPaginas() {
        this.acessos.forEach(e => {
            if(this.mutex == 0) {
                this.mutex = 1;
                this.procurarPagina(e);
                this.mutex = 0;
            }
        });
        clearInterval(this.interval);
        return this.qtdPageFault;
    }

    procurarPagina(pag) {
        let encontrou = false;

        let class0 = [];
        let class1 = [];
        let class2 = [];
        let class3 = [];

        for (let i = 0; i < this.lista.length; i++) {
            let q = this.lista[i];
            if (q.pag === pag) {
                encontrou = true;
                break;
            }
            switch (true) {
                case q.ref === 0 && q.mod === 0:
                    class0.push(i);
                    break;
                case q.ref === 0 && q.mod === 1:
                    class1.push(i);
                    break;
                case q.ref === 1 && q.mod === 0:
                    class2.push(i);
                    break;
                case q.ref === 1 && q.mod === 1:
                    class3.push(i);
                    break;
            }
        }

        if (!encontrou) {
            this.qtdPageFault++;

            let pObject = {
                "ref": 1,
                "mod": 1,
                "pag": pag
            };

            switch (true) {
                case class0.length != 0:
                    this.lista[Math.floor(Math.random() * (class0.length - 0)) + 0] = pObject;
                    break;
                case class1.length != 0:
                    this.lista[Math.floor(Math.random() * (class1.length - 0)) + 0] = pObject;
                    break;
                case class2.length != 0:
                    this.lista[Math.floor(Math.random() * (class2.length - 0)) + 0] = pObject;
                    break;
                case class3.length != 0:
                    this.lista[Math.floor(Math.random() * (class3.length - 0)) + 0] = pObject;
                    break;
            }
        }
    }
}