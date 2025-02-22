# Universidade de Brasília
## Programação para Sistemas Paralelos e Distribuídos
### Projeto Final - Kubernetes

#### Alunos
- Breno Henrique de Souza - 202015984
- Giulia Domingues de Alcantara - 180121308
- Samuel Alves Sato - 200069322
- Valderson Pontes da Silva Junior - 190020521

#### Introdução
O avanço da computação em nuvem e o uso crescente de contêineres têm impulsionado a adoção de tecnologias como o Kubernetes, que se tornou uma plataforma essencial para a orquestração de aplicações distribuídas. Neste contexto, o presente projeto busca explorar as capacidades de computação paralela e distribuída do Kubernetes, testando seu desempenho e tolerância a falhas em diferentes cenários.

O objetivo principal é avaliar o comportamento do Kubernetes em um ambiente de cluster self-hosted, composto por um nó mestre e pelo menos dois nós workers. Além disso, serão realizados experimentos integrando o Kubernetes com tecnologias complementares, como Apache Spark e bibliotecas MPI/OMP, analisando como cada abordagem impacta a escalabilidade, a resiliência e a eficiência do processamento distribuído.

A execução do projeto envolve a instalação e configuração do cluster Kubernetes, a implementação de uma aplicação de teste e a condução de experimentos que simulam falhas e variações na carga de trabalho. A partir dos resultados obtidos, será possível avaliar os benefícios e desafios do uso do Kubernetes para computação paralela e distribuída, bem como sua integração com outras tecnologias.

#### Metodologia
Para a realização da atividade proposta

#### Cluster Kubernetes
##### O que é 
Kubernetes é uma plataforma de código aberto, portátil e extensível para gerenciar cargas de trabalho e serviços conteinerizados. Ele facilita a configuração declarativa e a automação, permitindo que aplicações sejam executadas de forma eficiente e escalável. Com um ecossistema em rápido crescimento, Kubernetes oferece suporte a diversas ferramentas e serviços que auxiliam na administração e no funcionamento do cluster. [1]

Um cluster Kubernetes é formado por um conjunto de máquinas que trabalham juntas para executar aplicações em contêineres. Ele é composto por um plano de controle, responsável por gerenciar o cluster, manter o estado desejado e agendar workloads, e pelos nós workers, que são responsáveis por executar os contêineres e as aplicações. Dentro dos nós, os pods representam a menor unidade implantável e podem conter um ou mais contêineres, garantindo flexibilidade na execução das cargas de trabalho. [1]

Além da estrutura básica, Kubernetes possui mecanismos para gerenciar a comunicação entre as aplicações por meio de serviços, balanceamento de carga e recursos de rede. Também oferece opções para armazenamento, permitindo que os dados sejam mantidos de forma persistente ou temporária conforme a necessidade das aplicações. Para garantir a segurança, Kubernetes disponibiliza diversas configurações e políticas que ajudam a proteger os workloads e a definir boas práticas de administração do cluster. [1]

Em resumo, Kubernetes é uma solução poderosa para automatizar a implantação, escala e operação de aplicativos baseados em contêineres. Ele simplifica a gestão da infraestrutura, garantindo eficiência, flexibilidade e alta disponibilidade para aplicações modernas. [1]

![image](https://github.com/user-attachments/assets/f13e50c9-beed-48a1-875c-41ab9c8cd49e)


##### Passo a Passo de Montagem 
1. Criação do script de instalação básica do Kubernetes `common.sh`:
  - O script contém todos os comandos utilizados pelo grupo para a instalação das configurações;
  - Ele está disponível na pasta do projeto;
  - Esse arquivo deve ser executado nas três máquinas: master, worker01 e worker 02, com o comando:
    ```bash
    sudo ./common.sh
    ```
  - Para fazer com que o swapoff tem q tá desligado pros nós do cluster conectarem, dê o comando:
    ```bash
    sudo nano /etc/fstab
    ```
    E comente a linha do swap
2. Criação do script de configuração da master `master.sh`:
  - O script contém todos os comandos utilizados pelo grupo para a configuração da máquina master;
  - Ele está disponível na pasta do projeto;
  - Esse arquivo deve ser executado apenas na master, com o seguinte comando:
    ```bash
    bash ./master.sh
    ```
  - Após, rode:
    ```bash
    kubectl get po -n kube-system
    kubectl get --raw='/readyz?verbose'
    kubeadm token create --print-join-command
    ```
  O último comando retornará algo como:
  
        kubeadm join 10.0.0.10:6443 --token <TOKEN>  --discovery-token-ca-cert-hash <HASH SHA-256 >
3. Criação dos nós workers:
  - Em ambos os workrs, rode o comando que recebeu no print:
    * Obs: Recomenda-se a utilização de sudo para prevenir erros de permissão
    ```bash
    sudo kubeadm join 10.0.0.10:6443 --token <TOKEN>  --discovery-token-ca-cert-hash <HASH SHA-256 >
    ```
 4. Criação de labels:
  - No nó master rode:
    ```bash
    kubectl get nodes
    kubectl label node <nome-do-node> node-role.kubernetes.io/worker=worker
    ```
  5. Criação da aplicação nginx:
    -  Primeiro entre na pasta `manifests`:
    ```bash
    cd ../manifests
    ```
  - Após, dê os comandos:
    ```bash
    kubectl apply -f metrics-server.yaml
    kubectl top nodes
    kubectl apply -f sample-app.yaml
    ```
  - Entre na URL: https://<IP DA MAQUINA>:32000
##### Criação do Dashboard de Monitoramento:
- Instalação do `helm`:
  ```bash
  curl https://get.helm.sh/helm-v3.12.0-linux-amd64.tar.gz -o helm-v3.12.0-linux-amd64.tar.gz
  ```
- Adição do repositório kubernetes-dashboard
  ```bash
  helm repo add kubernetes-dashboard https://kubernetes.github.io/dashboard/
  ```
- Deploy de uma Release do Helm chamada 'kubernetes-dashboard' utilizando o chart do kubernetes-dashboard:
  ```bash
  helm upgrade --install kubernetes-dashboard kubernetes-dashboard/kubernetes-dashboard --create-namespace --namespace kubernetes-dashboard
  ```
- Habilitar o acesso ao Dashboard:
  ```bash
  kubectl -n kubernetes-dashboard port-forward svc/kubernetes-dashboard-kong-proxy 8443:443
  ```
- Acesse o link disponibilizado do dashboard via: [https://localhost:8443/](https://localhost:8443/)
- Criação do Usuário Admin `dashboard-adminuser.yaml`:
  - Criar o arquivo:
    ```bash
    nano dashboard-adminuser.yaml
    ```
  - Adicionar o conteúdo:
    ```bash
    apiVersion: v1
    kind: ServiceAccount
    metadata:
      name: admin-user
      namespace: kubernetes-dashboard
    apiVersion: rbac.authorization.k8s.io/v1
    kind: ClusterRoleBinding
    metadata:
      name: admin-user
    roleRef:
      apiGroup: rbac.authorization.k8s.io
      kind: ClusterRole
      name: cluster-admin
    subjects:
    - kind: ServiceAccount
      name: admin-user
      namespace: kubernetes-dashboard
    ```
    Se não funcionar:
    ```bash
    apiVersion: v1
    kind: ServiceAccount  
    metadata:
      name: admin-user
      namespace: kubernetes-dashboard
    ---
    apiVersion: rbac.authorization.k8s.io/v1
    kind: ClusterRoleBinding
    metadata:
      name: admin-user
    roleRef:
      apiGroup: rbac.authorization.k8s.io
      kind: ClusterRole
      name: cluster-admin
    subjects:
    - kind: ServiceAccount
      name: admin-user
      namespace: kubernetes-dashboard
    ```
  - Aplique as mudanças:
    ```bash
    kubectl apply -f dashboard-adminuser.yaml
    ```
- Gere o Token de Autenticação:
  ```bash
  kubectl -n kubernetes-dashboard create token admin-user
  ```
    * Obs: O dashbaord foi criado utilizando-se a documentação oficial do Kubernetes [2].

##### Testes e Resultados
###### 1. Teste de Alta Disponibilidade e Orquestração
- Verificando os pods criados:
![image](https://github.com/user-attachments/assets/1edc5216-ed0c-4e0e-a3d5-df2a99acde45)
- Simulando falha no pod:
![image](https://github.com/user-attachments/assets/88b71365-2fa4-42a0-a6f2-048fc5e1d43f)
- Kubernetes recriando o pod automaticamente:
![image](https://github.com/user-attachments/assets/d7790ecb-6063-4213-b8eb-24c61ae02758)
- Visualização no kubernetes dashboard:
![image](https://github.com/user-attachments/assets/1f7a4fb4-74f4-4606-b592-14680f59ae9d)
- Simulando a queda de um nó worker:
![image](https://github.com/user-attachments/assets/ed2fd8cc-34d1-4bb2-ba71-f64fb8f45377)
- Resultado no dashboard:
![image](https://github.com/user-attachments/assets/bab1db0d-9f3f-4d9c-a4d0-ece625dce744)
- O pod ficou pendente:
![image](https://github.com/user-attachments/assets/9a6c89de-2271-4fed-8088-021ff78490aa)
  - Obs: Caso o pod ainda esteja pendente e suba o worker de volta ele volta ao estado de running
- Criou um novo pod no worker:
![image](https://github.com/user-attachments/assets/92fd6c3d-9ea8-4359-9a56-ecd0806325cb)
  - Obs: Caso o pod tenha sido terminado, ele não cria o pod no worker ao subir de novo
- O pod foi deletado:
![image](https://github.com/user-attachments/assets/86210552-8296-4b6c-a2ab-1512aa7015a8)
- CPU ao longo do tempo:
![image](https://github.com/user-attachments/assets/fd156a13-7061-4bef-87e6-0f56a9146e86)

###### 2. Teste de Escalabilidade e Escalonamento:
- Criando mais replicas:
![image](https://github.com/user-attachments/assets/ad9c922c-1e18-4e81-b508-1270ed47e686)
- Analisando criação:
![image](https://github.com/user-attachments/assets/38180178-bec2-4968-81a5-894f48f5c07e)
- Criou com um nó ficando pendente:
![image](https://github.com/user-attachments/assets/aa110a1e-d7b8-4d62-8201-175bb907b258)
- No dashboard:
![image](https://github.com/user-attachments/assets/150c20b0-c859-4596-9b48-14be9f7c230a)
- Erro apresentado no nó:
![image](https://github.com/user-attachments/assets/c976e097-eb45-44b9-b099-08c8daa56bcc)
- Teste de carga:
![image](https://github.com/user-attachments/assets/59f4551e-df53-4ce6-a326-786212072871)
  - Comando no terminal windows: while ($true) { curl http://10.0.0.11:32000 } 
- Quando chega a 50% cria novas replicas:
![image](https://github.com/user-attachments/assets/5c72c020-ac9f-49bc-bdf9-f6fc084e5dca)
![image](https://github.com/user-attachments/assets/f011b24f-0676-4207-809d-623d4d4ca642)
![image](https://github.com/user-attachments/assets/71fa04ba-220f-463e-9da1-ef3ac2649e83)
- Uso da cpu aumentando:
![image](https://github.com/user-attachments/assets/dd244a49-94ed-4971-bd2a-5c37ec8b9a3c)

#### Spark com Kubernetes
##### Como funciona
A integração do Apache Spark com Kubernetes permite executar cargas de trabalho distribuídas de processamento de dados em um cluster Kubernetes, aproveitando seus recursos de escalabilidade e orquestração.

![image](https://github.com/user-attachments/assets/416288c8-fab7-45d0-b472-0538e5985ad0)

##### Passo a Passo de Montagem 
1. Instale o Apache Spark dentro da sua master:
  - Pré requisitos: [JAVA open SDK 11; Docker instalado](#anexos)
  - Rode os seguintes comandos:
    ```bash
    sudo mkdir -p /opt/spark
    ls /opt/
    sudo wget https://downloads.apache.org/spark/spark-3.5.4/spark-3.5.4-bin-hadoop3.tgz -P /opt/spark
    sudo tar -xvf /opt/spark/spark-3.5.4-bin-hadoop3.tgz -C /opt/spark --strip-components=1
    ls /opt/spark/bin/spark-submit
    export SPARK_HOME=/opt/spark
    export PATH=$PATH:$SPARK_HOME/bin 
    source ~/.bashrc
    spark-submit --version
    ```  
2. Baixe a imagem mais recente do Spark:
  ```bash
  sudo docker pull apache/spark:latest
  ```
4. Descubra o ip da sua master:
  ```bash
  kubectl cluster-info
  ```
5. Descubra o local do arquivo .jar:
  ```bash
  ls /opt/spark/examples/jars/
  ```
6. Execute o job Spark:
  ```bash
/opt/spark/bin/spark-submit \
    --master k8s://<IP DA MASTER>:<PORTA DA MASTER> \
    --deploy-mode cluster \
    --name spark-test \
    --class org.apache.spark.examples.SparkPi \
    --conf spark.executor.instances=3 \
    --conf spark.kubernetes.container.image=apache/spark:latest \
    local:///opt/spark/examples/jars/spark-examples_<VERSAO DO JAR>
  ```
  - Esse comando submete um job Spark ao Kubernetes para calcular uma aproximação do número π. Se bem sucedido ele retornará:
    ```bash
    INFO DAGScheduler: Job 0 finished: reduce at SparkPi.scala:36, took 20.123 s
    Pi is roughly 3.14159265358979
    ```
##### Testes e Resultados
###### 1. Teste de Carga
O teste foi feito

Resultados Apresentdos:

###### 2. Teste de Performance
O teste foi feito

Resultados Apresentados:

###### 3. Teste de Alta Disponibilidade
O teste foi feito

Resultados Apresentados:

###### 4. Teste de Escalabilidade
O teste foi feito

Resultados Apresentados:

###### 5. Teste de Orquestração
O teste foi feito

Resultados Apresentados:

###### 6. Teste de Escalonamento
O teste foi feito

Resultados Apresentados:

#### MPI/OpenMP com Kubernetes
##### Como funciona
A integração do Spark com o Kubernetes...
##### Passo a Passo de Montagem 

##### Testes e Resultados
###### 1. Teste de Carga
O teste foi feito

Resultados Apresentdos:

###### 2. Teste de Performance
O teste foi feito

Resultados Apresentados:

###### 3. Teste de Alta Disponibilidade
O teste foi feito

Resultados Apresentados:

###### 4. Teste de Escalabilidade
O teste foi feito

Resultados Apresentados:

###### 5. Teste de Orquestração
O teste foi feito

Resultados Apresentados:

###### 6. Teste de Escalonamento
O teste foi feito

Resultados Apresentados:

#### Cloud Native
##### O que é 
Cloud Native é 
##### Tópico 2
##### Tópico 3
##### Tópico 4

#### Conclusão 
##### Sobre o Experimento

##### Percepção dos Estudantes

##### Autoavaliação 

##### Referências
[1] KUBERNETES. Conceitos. Disponível em: [https://kubernetes.io/docs/concepts/](https://kubernetes.io/docs/concepts/). Acesso em: 20 fev. 2025.

[2] KUBERNETES. Dashboard. Disponível em: [https://kubernetes.io/docs/tasks/access-application-cluster/web-ui-dashboard/](https://kubernetes.io/docs/tasks/access-application-cluster/web-ui-dashboard/). Acesso em: 20 fev. 2025. 

#### Anexos
##### Manual de instalação das VMs 
- Pré-Requisitos:
  - [Virtual Box](https://www.virtualbox.org/wiki/Downloads)
  - [Vagrant](https://developer.hashicorp.com/vagrant/install)
- Após baixar o Vagrant, execute:
    ```bash
      mkdir apache-vm && cd apache-vm
      vagrant init bento/ubuntu-22.04 
    ```
  - Modifique o Vagrantfile para:
    ```bash
        Vagrant.configure("2") do |config|
          config.vm.provision "shell", inline: <<-SHELL
              apt-get update -y
              echo "10.0.0.10  master-node" >> /etc/hosts
              echo "10.0.0.11  worker-node01" >> /etc/hosts
              echo "10.0.0.12  worker-node02" >> /etc/hosts
          SHELL
          
          config.vm.define "master-spark" do |master|
            master.vm.box = "bento/ubuntu-22.04"
            master.vm.hostname = "master-node"
            master.vm.network "private_network", ip: "10.0.0.10"
            master.vm.provider "virtualbox" do |vb|
                vb.memory = 8192 
                vb.cpus = 4
            end
          end
        
          (1..2).each do |i|
        
          config.vm.define "node0#{i}-spark" do |node|
            node.vm.box = "bento/ubuntu-22.04"
            node.vm.hostname = "worker-node0#{i}"
            node.vm.network "private_network", ip: "10.0.0.1#{i}"
            node.vm.provider "virtualbox" do |vb|
                vb.memory = 4096
                vb.cpus = 2
            end
          end
          
          end
        end
    ```
  - Após, execute para subir as VMs:
    ```bash
      vagrant up 
    ```
#### Configuração do Java openJDK11
Para instalar o Java openJDK11 execute os seguintes comandos
```bash
  sudo apt update
  sudo apt install openjdk-11-jdk
  java -version
  ```
##### Configuração do Docker no Kubernetes
```bash
  sudo apt update && sudo apt upgrade -y
  sudo apt install -y ca-certificates curl gnupg
  sudo install -m 0755 -d /etc/apt/keyrings
  curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo tee /etc/apt/keyrings/docker.asc > /dev/null
  echo "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
  sudo apt update
  sudo apt install -y docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
  docker --version
  ```
