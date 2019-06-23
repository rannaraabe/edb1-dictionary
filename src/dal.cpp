#include <iostream>
#include "../include/dictionary.h"

template <typename Key, typename Data, typename KeyComparator>
DAL<Key, Data, KeyComparator>::DAL(int _MaxSz)
{
    mi_Capacity = _MaxSz;
    mi_Length = 0;
    mpt_Data = new NodeAL[_MaxSz];
}

template <typename Key, typename Data, typename KeyComparator>
DAL<Key, Data, KeyComparator>::~DAL()
{
    delete[] mpt_Data;
}

template <typename Key, typename Data, typename KeyComparator>
bool DAL<Key, Data, KeyComparator>::insert(const Key &new_k, Data &new_d)
{

    // Confere se na lista já existe essa chave
    if (not(_search(new_k) == -1))
        return false;

    // Confere se a lista está cheia
    if (full())
        // Solicita mais espaço no vetor para adicionar o novo valor
        reserve(mi_Capacity * 2);

    NodeAL node(new_k, new_d);    // Cria um nó com o par de dados do que será inserido
    mpt_Data[mi_Length++] = node; // Adi

    return true;
}

template <typename Key, typename Data, typename KeyComparator>
bool DAL<Key, Data, KeyComparator>::remove(const Key &k, Data &d)
{
    // Confere se a lista está vazia
    if (empty())
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
            d = mpt_Data[i].info;
            mpt_Data[i] = mpt_Data[--mi_Length];
        }
    }
}

template <typename Key, typename Data, typename KeyComparator>
bool DAL<Key, Data, KeyComparator>::search(const Key &k, Data &d)
{
    // Recebe o retorna da busca auxiliar para verificar se existe algum dado com essa chave
    int i = _search(k);

    if (i == -1)
        return false;
    else
    {
        // Elemento foi encontrado
        d = mpt_Data[i].info;

        return true;
    }
}

// template <typename Key, typename Data, typename KeyComparator>
// Key DAL<Key, Data, KeyComparator>::max() const
// {
// }

// template <typename Key, typename Data, typename KeyComparator>
// Key DAL<Key, Data, KeyComparator>::min() const
// {
// }

template <typename Key, typename Data, typename KeyComparator>
bool DAL<Key, Data, KeyComparator>::predecessor(const Key &key, Key &chave) const
{
    // Chave de comparacao
    int max = key;

    // Caso a chave passada seja igual a chave a de comparacao
    if (max == key)
        return false;
    else
    {
        // Percorre a lista inteira comparando os valores da chave com max
        for (int i{0}; i < mi_Length; i++)
        {
            // Caso a chave seja menor do que a chave de comparacao, continuará buscando
            if (mpt_Data[i].id < key)
            {
                // Caso exista um valor de chave maior do que a chave de comparacao
                if (mpt_Data[i].id > max)
                    max = mpt_Data[i].id; // Nova valor maximo
            }
        }
    }

    // Atribui o valor max achado para chave
    chave = max;
    return true;
}

template <typename Key, typename Data, typename KeyComparator>
bool DAL<Key, Data, KeyComparator>::sucessor(const Key &key, Key &chave) const
{
    // Chave de comparacao
    int min = key;

    // Caso a chave passada seja igual a chave a de comparacao
    if (min == key)
        return false;
    else
    {
        // Percorre a lista inteira comparando os valores da chave com min
        for (int i{0}; i < mi_Length; i++)
        {
            // Caso a chave seja maior do que a chave de comparacao, continuará buscando
            if (mpt_Data[i].id > key)
            {
                // Caso exista um valor de chave menor do que a chave de comparacao
                if (mpt_Data[i].id < min)
                    min = mpt_Data[i].id; // Nova valor minimo
            }
        }
    }

    // Atribui o valor min achado para chave
    chave = min;
    return true;
}
