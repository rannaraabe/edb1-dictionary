/** 
 * @file dsal.cpp
 * @author Ranna Raabe
 */

#include "../include/dictionary.h"

/// Método de busca auxiliar
template <typename Key, typename Data, typename KeyComparator>
int DSAL<Key, Data, KeyComparator>::_search(const Key &key) const
{
    int first = 0;
	int last = this->mi_Length;

    while (first != last)
    {
        int m = first + (last - first) / 2;

        if (this->mpt_Data[m].id == key)
            return m;
        else if (this->mpt_Data[m].id > key)
            last = m - 1;
        else
            first = m + 1;
    }

    return -1;
}

/// Insere um novo valor associada a uma nova chave no dicionario
template <typename Key, typename Data, typename KeyComparator>
bool DSAL<Key, Data, KeyComparator>::insert(const Key &new_k, const Data &new_d)
{
    KeyComparator k_comp; // Functor
    NodeAL *pivot;        // Cria um nó com o par de dados do que será inserido
    int dis;

    // Confere se na lista já existe essa chave
    if (not(_search(new_k) == -1))
        return false;

    // Confere se a lista está cheia
    if (this->mi_Length == this->mi_Capacity)
        // Solicita mais espaço no vetor para adicionar o novo valor
        this->reserve(this->mi_Length * 2);
    else
    {
        for (auto i = this->mpt_Data; i < this->mpt_Data + this->mi_Length; ++i)
        {
            // Confere se a nova chave eh menor do que a chave da posicao atual (eh preciso inserir seguindo a ordem)
            if (k_comp(new_k, i->id))
            {
                pivot = i;
                dis = i - this->mpt_Data;

                for (int i = this->mi_Length; i > dis; --i)
                    this->mpt_Data[i] = this->mpt_Data[i - 1];

                // Adicionando o valor
                *pivot = NodeAL(new_k, new_d);
                this->mi_Length++;

                return true;
            }
        }
    }
}

/// Deleta um valor associada a uma chave no dicionario
template <typename Key, typename Data, typename KeyComparator>
bool DSAL<Key, Data, KeyComparator>::remove(const Key &k, Data &d)
{
    // Confere se a lista está vazia
    if (this->mi_Length < 1)
        return false;
    else
    {
        // Recebe o retorna da busca auxiliar para verificar se existe algum dado com essa chave
        int i = _search(k);

        if (i == -1)
            return false;
        else
        {
            // Removendo o dado da lista
            d = this->mpt_Data[i].info;
            std::copy(this->mpt_Data + i + 1, this->mpt_Data + this->mi_Length, this->mpt_Data + i);
            this->mi_Length--;

            return true;
        }
    }
}

/// Recupera a maior chave do dicionario
template <typename Key, typename Data, typename KeyComparator>
Key DSAL<Key, Data, KeyComparator>::max() const
{
    // Confere se a lista está vazia
    if (this->mi_Length < 1)
        std::cout << "Dicionario vazio";
    else
        return this->mpt_Data[this->mi_Length - 1].id; // Retorna a ultima chave, afinal a lista está ordenada
}

/// Recupera a menor chave do dicionario
template <typename Key, typename Data, typename KeyComparator>
Key DSAL<Key, Data, KeyComparator>::min() const
{
    // Confere se a lista está vazia
    if (this->mi_Length < 1)
        std::cout << "Dicionario vazio";
    else
        return this->mpt_Data[0].id; // Retorna a primeira chave, afinal a lista está ordenada
}

/// Recupera em \chave a chave antecessora a key, se existir retorna true
template <typename Key, typename Data, typename KeyComparator>
bool DSAL<Key, Data, KeyComparator>::predecessor(const Key &key, Key &chave) const
{
    // Recebe o retorna da busca auxiliar
    int i = _search(key);

    // Caso a chave seja 0, não tem antecessor
    if (i == 0)
        return false;
    else
    {
        // Recupera a chave do antecessor
        chave = this->mpt_Data[i - 1].id;
        return true;
    }
}

/// Recupera em \chave a chave sucessora a key, se existir retorna true
template <typename Key, typename Data, typename KeyComparator>
bool DSAL<Key, Data, KeyComparator>::successor(const Key &key, Key &chave) const
{
    // Recebe o retorna da busca auxiliar
    int i = _search(key);

    // Caso a chave seja a ultima, nao tem sucessor
    if (i == this->mi_Length - 1)
        return false;
    else
    {
        // Recupera a chave do sucessor
        chave = this->mpt_Data[i + 1].id;
        return true;
    }
}