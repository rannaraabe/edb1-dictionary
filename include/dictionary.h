/** 
 * @file dictionary.h
 * @author Ranna Raabe
 */

#include <iostream>
#include <string>
#include <functional>

// using Key = int;          //!< Alias para chave
// using Data = std::string; //!< ALias para o dado

/** Classe representando um dicionário com armazenamento
 * em um vetor não ordenado.
 */
template <typename Key, typename Data, typename KeyComparator = std::less<int>>
class DAL
{
  protected:
    /** Estrutura do nó, representando o par chave-informaçao
     */
    struct NodeAL
    {
        Key id;    //!< A chave eh um inteiro simples
        Data info; //!< A informacao eh uma cadeia de caracteres

        NodeAL(Key _id = Key(), Data _info = Data())
            : id(_id), info(_info){
                           /*empty*/
                       };
    };

    static const int SIZE = 50; //!< Tamanho default da lista
    int mi_Length;              //!< Tamanho atual da litsa
    int mi_Capacity;            //!< capacidade máxima da armazenamento
    NodeAL *mpt_Data;           // Área de armazenamento: vetor alocado dinamicamente

    /** Método de busca auxiliar
     */
    int _search(const Key &key)
    {
        for (int i{0}; i < mi_Length; i++)
        {
            if (mpt_Data[i].id == key)
                return i;
        }

        return -1;
    };

  public:
    /** Construtor default
     */
    DAL(int _MaxSz = SIZE)
    {
        mi_Capacity = _MaxSz;
        mi_Length = 0;
        mpt_Data = new NodeAL[_MaxSz];
    };

    /** Destrutor
     */
    virtual ~DAL()
    {
        delete[] mpt_Data;
    };

    /** Insere um novo valor associada a uma nova chave no dicionario.
     * 
     * @param new_k - chave a qual o valor será associado
     * @param new_d - valor que será adicionado no dicionário
     */
    bool insert(const Key &new_k, const Data &new_d)
    {
        // Confere se na lista já existe essa chave
        if (not(_search(new_k) == -1))
            return false;

        // Confere se a lista está cheia
        if (!(mi_Length < mi_Capacity))
            // Solicita mais espaço no vetor para adicionar o novo valor
            reserve(mi_Length * 2);

        NodeAL node(new_k, new_d);    // Cria um nó com o par de dados do que será inserido
        mpt_Data[mi_Length++] = node; // Adicionando o valor

        // this->mpt_Data[mi_Lenght].id = new_k;
        // this->mpt_Data[mi_Lenght].info = new_d;
        // mi_Lenght++;

        return true;
    };

    /** Deleta um valor associada a uma chave no dicionario.
     * 
     * @param k - chave a qual o valor será associado
     * @param d - valor que será adicionado no dicionário
     */
    bool remove(const Key &k, Data &d)
    {
        // Confere se a lista está vazia
        if (mi_Capacity == 0)
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
                mpt_Data[i] = mpt_Data[mi_Length--];

                return true;
            }
        }
    };

    /** Reserva \sz elementos
     * 
     * @param sz - quantidade necessaria
     */
    bool reserve(size_t sz)
    {
        NodeAL *node = new NodeAL[sz];

        for (int i = 0; i < mi_Capacity; i++)
        {
            node[i].id = this->mpt_Data[i].id;
            node[i].info = this->mpt_Data[i].info;
        }

        delete[] mpt_Data;
        this->mpt_Data = node;

        this->mi_Capacity = sz;
        return true;
    };

    /** Busca um valor associada a uma chave no dicionario.
     * 
     * @param k - chave a qual o valor será associado
     * @param d - valor que será adicionado no dicionário
     */
    bool search(const Key &k, Data &d)
    {
        // Recebe o retorna da busca auxiliar para verificar se existe algum dado com essa chave
        int i = _search(k);

        if (i == -1)
            return false;
        else
        {
            // Elemento foi encontrado
            d = mpt_Data[i].info;
        }

        return true;
    };

    /** Recupera a maior chave do dicionario
     */
    Key max(void) const
    {
        KeyComparator k_comp;     // Functor
        Key max = mpt_Data[0].id; // Define o primeiro valor da lista como o max, apenas para comparar depois

        // Confere se a lista está vazia
        // if (this->mi_Length == 0)
        //     throw std::out_of_range("Dicionario vazio");

        for (int i{1}; i < mi_Length; i++) // Começo da segunda posição da lista
        {
            if (k_comp(max, mpt_Data[i].id)) // Compara a chave definida como max com cada chave da lista
                max = mpt_Data[i].id;
        }

        return max;
    };

    /** Recupera a menor chave do dicionario
     */
    Key min(void) const
    {
        KeyComparator k_comp;     // Functor
        Key min = mpt_Data[0].id; // Define o primeiro valor da lista como o min, apenas para comparar depois

        // Confere se a lista está vazia
        // if (this->mi_Length == 0)
        //     throw std::out_of_range("Dicionario vazio");

        for (int i{1}; i < mi_Length; i++) // Começo da segunda posição da lista
        {
            if (k_comp(mpt_Data[i].id, min)) // Compara a chave definida como min com cada chave da lista
                min = mpt_Data[i].id;
        }

        return min;
    };

    /** Recupera em \chave a chave antecessora a key, se existir retorna true
     * 
     * @param key - 
     * @param chave -
     */
    bool predecessor(const Key &key, Key &chave) const
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
    };

    /** Recupera em \chave a chave sucessora a key, se existir retorna true
     *
     * @param key - 
     * @param chave -
     */
    bool successor(const Key &key, Key &chave) const
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
    };

    /** Envia de volta para o fluxo de saída uma representação ascii para a lista
     */
    inline friend std::ostream &operator<<(std::ostream &_os, const DAL &_oList)
    {
        _os << "[ ";
        for (int i(0); i < _oList.mi_Length; ++i)
            _os << "{id: " << _oList.mpt_Data[i].id << ", info: "
                << _oList.mpt_Data[i].info << "} ";
        _os << "]";

        return _os;
    };
};

/** Classe representando um dicionário com armazenamento
 * em um vetor ordenado.
 */
template <typename Key, typename Data, typename KeyComparator = std::less<int>>
class DSAL : public DAL<Key, Data, KeyComparator>
{
    using NodeAL = typename DAL<Key, Data, KeyComparator>::NodeAL;

  public:
    /** Construtor default
         */
    DSAL(int _MaxSz = DAL<Key, Data, KeyComparator>::SIZE)
        : DAL<Key, Data, KeyComparator>(_MaxSz){
              /*empty*/
          };

    /** Destrutor
         */
    virtual ~DSAL(){
        /*empty*/
    };

    /** Insere um novo valor associada a uma nova chave no dicionario.
     * 
     * @param new_k - chave a qual o valor será associado
     * @param new_d - valor que será adicionado no dicionário
     */
    bool insert(const Key &new_k, const Data &new_d)
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
                }
            }
        }

        return true;
    };

    /** Deleta um valor associada a uma chave no dicionario.
     * 
     * @param k - chave a qual o valor será associado
     * @param d - valor que será adicionado no dicionário
     */
    bool remove(const Key &k, Data &d)
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
            }
        }
        return true;
    };

    /** Busca um valor associada a uma chave no dicionario.
     * 
     * @param k - chave a qual o valor será associado
     * @param d - valor que será adicionado no dicionário
     */
    //bool search(const Key &k, Data &d);

    /** Recupera a maior chave do dicionario
     */
    Key max() const
    {
        Key aux;

        // Confere se a lista está vazia
        // if (this->mi_Length < 1)
        //     throw std::out_of_range("Dicionario vazio");

        aux = this->mpt_Data[this->mi_Length - 1].id; // Retorna a ultima chave, afinal a lista está ordenada

        return aux;
    };

    /** Recupera a menor chave do dicionario
     */
    Key min() const
    {
        Key aux;

        // Confere se a lista está vazia
        // if (this->mi_Length < 1)
        //     throw std::out_of_range("Dicionario vazio");

        aux = this->mpt_Data[0].id; // Retorna a primeira chave, afinal a lista está ordenada

        return aux;
    };

    /** Recupera em \chave a chave antecessora a key, se existir retorna true
     * 
     * @param key - 
     * @param chave -
     */
    bool predecessor(const Key &key, Key &chave) const
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
        }
        return true;
    };

    /** Recupera em \chave a chave sucessora a key, se existir retorna true
     *
     * @param key - 
     * @param chave -
     */
    bool successor(const Key &key, Key &chave) const
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
        }
        return true;
    };

    /** Método de busca auxiliar
     */
    int _search(const Key &key) const
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
    };
};
