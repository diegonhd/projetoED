import ctypes
from ctypes import Structure, c_char, c_char_p, c_int, c_float, c_void_p, c_bool, byref, POINTER

# carrega a dll com o código da lista
lib = ctypes.CDLL("./lista.dll")

# define a struct Operation
class Operation(Structure):
    _fields_ = [("id", c_int),
                ("value", c_float),
                ("type", c_char * 15),
                ("date", c_char * 20),
                ("instituicao", c_char * 10),
                ("destino", c_char * 30)]

# define a struct TElementoLista
class TElementoLista(Structure):
    _fields_ = [("data", POINTER(Operation)),
                ("nextElemento", c_void_p),
                ("prevElemento", c_void_p)]

# define a struct TLista
class TLista(Structure):
    _fields_ = [("nElementos", c_int),
                ("sizeElemento", c_int),
                ("saldo", c_float),
                ("first", POINTER(TElementoLista)),
                ("last", POINTER(TElementoLista)),
                ("current", POINTER(TElementoLista))]


# configura os tipos dos argumentos e retorno da função Lista_cria
lib.Lista_cria.argtypes = [POINTER(TLista)]
lib.Lista_cria.restype = None

# configura os tipos dos argumentos e retorno da função Lista_next
lib.Lista_next.argtypes = [POINTER(TLista)]
lib.Lista_next.restype = c_bool

# configura os tipos dos argumentos e retorno da função Lista_prev
lib.Lista_prev.argtypes = [POINTER(TLista)]
lib.Lista_prev.restype = c_bool

# configura os tipos dos argumentos e retorno da função Lista_getSize
lib.Lista_getSize.argtypes = [POINTER(TLista)]
lib.Lista_getSize.restype = c_int

# configura os tipos dos argumentos e retorno da função Lista_goFirst
lib.Lista_goFirst.argtypes = [POINTER(TLista)]
lib.Lista_goFirst.restype = None

# configura os tipos dos argumentos e retorno da função Lista_goLast
lib.Lista_goLast.argtypes = [POINTER(TLista)]
lib.Lista_goLast.restype = None

# configura os tipos dos argumentos e retorno da função realizar_deposito
lib.realizar_deposito.argtypes = [POINTER(TLista), c_float, c_char_p]
lib.realizar_deposito.restype = c_bool

# configura os tipos dos argumentos e retorno da função realizar_saque
lib.realizar_saque.argtypes = [POINTER(TLista), c_float, c_char_p]
lib.realizar_saque.restype = c_bool

# configura os tipos dos argumentos e retorno da função realizar_transferencia
lib.realizar_transferencia.argtypes = [POINTER(TLista), c_float, c_char_p, c_char_p]
lib.realizar_transferencia.restype = c_bool

# configura os tipos dos argumentos e retorno da função get_currentOperation
lib.get_currentOperation.argtypes = [POINTER(TLista)]
lib.get_currentOperation.restype = POINTER(Operation)

# configura os tipos dos argumentos e retorno da função get_firstOperation
lib.get_firstOperation.argtypes = [POINTER(TLista)]
lib.get_firstOperation.restype = POINTER(Operation)

# configura os tipos dos argumentos e retorno da função get_lastOperation
lib.get_lastOperation.argtypes = [POINTER(TLista)]
lib.get_lastOperation.restype = POINTER(Operation)

# configura os tipos dos argumentos e retorno da função get_allOperations
lib.get_allOperations.argtypes = [POINTER(TLista)]
lib.get_allOperations.restype = c_char_p

# configura os tipos dos argumentos e retorno da função get_fiveOperations
lib.get_fiveOperations.argtypes = [POINTER(TLista)]
lib.get_fiveOperations.restype = c_char_p

# configura os tipos dos argumentos e retorno da função get_saldo
lib.get_saldo.argtypes = [POINTER(TLista)]
lib.get_saldo.restype = c_float



lista = TLista()
lib.Lista_cria(byref(lista))

lib.realizar_deposito(byref(lista), 100, b"25/07/2025")
lib.realizar_saque(byref(lista), 45, b"25/07/2025")
lib.realizar_transferencia(byref(lista), 34, b"25/07/2025", b"Diego")

# deselvolvimento da lógica do backend em si
from flask import Flask, jsonify, request
from flask_cors import CORS
import json

app = Flask(__name__)
port = 3000

CORS(app)

@app.route("/operation/all", methods=["GET"])
def get_allOperations():
    jsontexto = lib.get_allOperations(byref(lista)).decode()
    jsontexto = json.loads(jsontexto)
    return jsonify(jsontexto)

@app.route("/operation/lasts", methods=["GET"])
def get_fiveOperations():
    jsontexto = lib.get_fiveOperations(byref(lista)).decode()
    jsontexto = json.loads(jsontexto)
    return jsonify(jsontexto)

@app.route("/operation/<int:id>", methods=["GET"])
def get_operationById(id):
    lib.Lista_goFirst(byref(lista))

    for i in range(lib.Lista_getSize(byref(lista))):
        atual = lib.get_currentOperation(byref(lista))
        if atual.contents.id == id:
            operation = {"id": atual.contents.id,
                         "value": atual.contents.value,
                         "type": atual.contents.type.decode(),
                         "date": atual.contents.date.decode(),
                         "instituicao": atual.contents.instituicao.decode(),
                         "destino": atual.contents.destino.decode()}
            return jsonify(operation)
        
        lib.Lista_next(byref(lista))
    
    return jsonify({"erro": "Operação não encontrada"}), 404

@app.route("/operation/saldo", methods=["GET"])
def get_saldo():
    saldo = lib.get_saldo(byref(lista))
    return jsonify({"saldo": saldo})

@app.route("/operation/deposit", methods=["POST"])
def create_deposit():
    deposit = request.json
    lib.realizar_deposito(byref(lista), deposit["value"], deposit["date"].encode())
    return deposit

@app.route("/operation/withdrawal", methods=["POST"])
def create_withdrawal():
    withdrawal = request.json
    lib.realizar_saque(byref(lista), withdrawal["value"], withdrawal["date"].encode())
    return withdrawal

@app.route("/operation/transfer", methods=["POST"])
def create_transfer():
    transfer = request.json
    lib.realizar_transferencia(byref(lista), transfer["value"], transfer["date"].encode(), transfer["destino"].encode())
    return transfer


app.run(port=port)
