/** 
 * @file dictionary.h
 * @author Ranna Raabe
 */

#include <iostream>
#include <string>
#include <functional>

/** Classe representando um dicionário com armazenamento
 * em um vetor não ordenado.
 */
template <class Key, class Data, class KeyComparator = std::less<int>>
class DAL
{
  protected:
    // using Key = int;          //!< Alias para chave
    // using Data = std::string; //!< ALias para o dado

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
    int _search(const Key &key);

  public:
    /** Construtor default
     */
    DAL(int _MaxSz = SIZE);

    /** Destrutor
     */
    virtual ~DAL();

    /** Insere um novo valor associada a uma nova chave no dicionario.
     * 
     * @param new_k - chave a qual o valor será associado
     * @param new_d - valor que será adicionado no dicionário
     */
    bool insert(const Key &new_k, const Data &new_d);

    /** Deleta um valor associada a uma chave no dicionario.
     * 
     * @param k - chave a qual o valor será associado
     * @param d - valor que será adicionado no dicionário
     */
    bool remove(const Key &k, Data &d);

    /** Reserva \sz elementos
     * 
     * @param sz - quantidade necessaria
     */ 
    bool reserve(size_t sz);

    /** Busca um valor associada a uma chave no dicionario.
     * 
     * @param k - chave a qual o valor será associado
     * @param d - valor que será adicionado no dicionário
     */
    bool search(const Key &k, Data &d);

    /** Recupera a maior chave do dicionario
     */
    Key max(void) const;

    /** Recupera a menor chave do dicionario
     */
    Key min(void) const;

    /** Recupera em \chave a chave antecessora a key, se existir retorna true
     * 
     * @param key - 
     * @param chave -
     */
    bool predecessor(const Key &key, Key &chave) const;

    /** Recupera em \chave a chave sucessora a key, se existir retorna true
     *
     * @param key - 
     * @param chave -
     */
    bool successor(const Key &key, Key &chave) const;

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
    }
};

/** Classe representando um dicionário com armazenamento
 * em um vetor ordenado.
 */
template <class Key, class Data, class KeyComparator = std::less<int>>
class DSAL : public DAL<Key, Data, KeyComparator>
{
    using NodeAL = typename DAL<Key, Data, KeyComparator>::NodeAL;

  public:
    
    /** Construtor default
         */
    DSAL(int _MaxSz = DAL<Key, Data, KeyComparator>::SIZE)
        : DAL<Key, Data, KeyComparator>(_MaxSz)
    {
        /*empty*/
    }

    /** Destrutor
         */
    virtual ~DSAL()
    {
        /*empty*/
    }

    /** Insere um novo valor associada a uma nova chave no dicionario.
     * 
     * @param new_k - chave a qual o valor será associado
     * @param new_d - valor que será adicionado no dicionário
     */
    bool insert(const Key &new_k, const Data &new_d);

    /** Deleta um valor associada a uma chave no dicionario.
     * 
     * @param k - chave a qual o valor será associado
     * @param d - valor que será adicionado no dicionário
     */
    bool remove(const Key &k, Data &d);

    /** Busca um valor associada a uma chave no dicionario.
     * 
     * @param k - chave a qual o valor será associado
     * @param d - valor que será adicionado no dicionário
     */
    bool search(const Key &k, Data &d);

    /** Recupera a maior chave do dicionario
     */
    Key max() const;

    /** Recupera a menor chave do dicionario
     */
    Key min() const;

    /** Recupera em \chave a chave antecessora a key, se existir retorna true
     * 
     * @param key - 
     * @param chave -
     */
    bool predecessor(const Key &key, Key &chave) const;

    /** Recupera em \chave a chave sucessora a key, se existir retorna true
     *
     * @param key - 
     * @param chave -
     */
    bool successor(const Key &key, Key &chave) const;

    /** Método de busca auxiliar
     */
    int _search(const Key &key) const;
};
