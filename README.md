# Universidade de Brasília
## Programação para Sistemas Paralelos e Distribuídos
### Projeto Final - Kubernetes

#### Alunos
- Breno Henrique de Souza - 202015984
- Giulia Domingues de Alcantara - 180121308
- Samuel Alves Sato - 200069322
- Valderson Pontes da Silva Junior - 190020521

#### Introdução
Este relatório tem como objetivo documentar.

#### Metodologia
Para a realização da atividade proposta

#### Cluster Kubernetes
##### O que é 
Kubernetes é uma plataforma de código aberto, portátil e extensível para gerenciar cargas de trabalho e serviços conteinerizados. Ele facilita a configuração declarativa e a automação, permitindo que aplicações sejam executadas de forma eficiente e escalável. Com um ecossistema em rápido crescimento, Kubernetes oferece suporte a diversas ferramentas e serviços que auxiliam na administração e no funcionamento do cluster. [1]

Um cluster Kubernetes é formado por um conjunto de máquinas que trabalham juntas para executar aplicações em contêineres. Ele é composto por um plano de controle, responsável por gerenciar o cluster, manter o estado desejado e agendar workloads, e pelos nós workers, que são responsáveis por executar os contêineres e as aplicações. Dentro dos nós, os pods representam a menor unidade implantável e podem conter um ou mais contêineres, garantindo flexibilidade na execução das cargas de trabalho. [1]

Além da estrutura básica, Kubernetes possui mecanismos para gerenciar a comunicação entre as aplicações por meio de serviços, balanceamento de carga e recursos de rede. Também oferece opções para armazenamento, permitindo que os dados sejam mantidos de forma persistente ou temporária conforme a necessidade das aplicações. Para garantir a segurança, Kubernetes disponibiliza diversas configurações e políticas que ajudam a proteger os workloads e a definir boas práticas de administração do cluster. [1]

Em resumo, Kubernetes é uma solução poderosa para automatizar a implantação, escala e operação de aplicativos baseados em contêineres. Ele simplifica a gestão da infraestrutura, garantindo eficiência, flexibilidade e alta disponibilidade para aplicações modernas. [1]

##### Passo a Passo de Montagem 
1. Criação do script de instalação básica do Kubernetes `common.sh`:
  - O script contém todos os comandos utilizados pelo grupo para a instalação das configurações;
  - Ele está disponível na pasta do projeto;
  - Esse arquivo deve ser executado nas três máquinas: master, worker01 e worker 02, com o comando:
  ```bash
  sudo ./common.sh
  ```
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
    ```bash
    kubeadm join 10.0.0.10:6443 --token <TOKEN>  --discovery-token-ca-cert-hash <HASH SHA-256 >
    ```
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
    kubectl apply -f sample-app.yaml
    kubectl top nodes
    ```
  - Entre na URL: [https://localhost:32000](https://localhost:32000)
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
###### 1. Teste de Escalabilidade
O teste foi feito

Resultados Apresentados:

###### 2. Teste de Orquestração
O teste foi feito

Resultados Apresentados:

###### 3. Teste de Alta Disponibilidade
O teste foi feito

Resultados Apresentados:

###### 4. Teste de Escalonamento
O teste foi feito

Resultados Apresentados:

#### Spark com Kubernetes
##### Como funciona
A integração do Spark com o Kubernetes...
##### Passo a Passo de Montagem 
1. Instale o Apache Spark dentro da sua master:
  - Pré requisitos: JAVA open SDK 11; Docker instalado
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
2. Se não tiver o Docker instalado, instale-o:
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
3. Baixe a imagem mais recente do Spark:
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
    --master k8s://https://<IP DA MASTER>:<PORTA DA MASTER> \
    --deploy-mode client \ 
    --name spark-test \
    --class org.apache.spark.examples.SparkPi \
    --conf spark.executor.instances=3 \
    --conf spark.kubernetes.container.image=apache/spark:latest \
    --conf spark.eventLog.enabled=true \
    --conf spark.eventLog.dir=file:///tmp/spark-events \
    local:///<LOCAL DO JAR>
  ```
  - Verifique o histórico do job na URL: [<IP DA MASTER>:18080](<IP DA MASTER>:18080)
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

#### Configuração do Java JDK11

##### Configuração do Docker no Kubernetes
