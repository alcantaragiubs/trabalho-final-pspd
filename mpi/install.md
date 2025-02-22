
Tutorial usado 

https://kubernetes.io/pt-br/docs/setup/production-environment/tools/kubeadm/install-kubeadm/


curl -fsSL https://pkgs.k8s.io/core:/stable:/v1.33/deb/Release.key | sudo gpg --dearmor -o /etc/apt/keyrings/kubernetes-apt-keyring.gpgCópia

echo 'deb [signed-by=/etc/apt/keyrings/kubernetes-apt-keyring.gpg] https://pkgs.k8s.io/core:/stable:/v1.33/deb/ /' | sudo tee /etc/apt/sources.list.d/kubernetes.listCópia

sudo apt update

sudo apt install kubeadm kubelet kubectl
