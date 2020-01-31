#include "PQE\PurpleDreamElf.h"
#include "fbxsdk.h"
#include<algorithm>
#include<functional>
namespace PQE
{

	class PQE_MODEL;
	class PQE_NODE;
	class PQE_MESH;
	class PQE_MATERIAL;
	class PQE_TEXTURE;
	class PQE_MATRIX;
	class AABB;

	class PQE_MODEL
	{
	public:
		PQE_MODEL();
		~PQE_MODEL();
	public:
		unsigned int		meshNum;		//��������
		unsigned int		shapeNum;		//��������
		unsigned int		materialNum;	//��������
		unsigned int		textureNum;		//��������
		unsigned int        matrixNum;		//��������
		PQE_NODE			*mRootNode;		//���ڵ�
		PQE_MATRIX			*mMatrix;		//����
		PQE_MESH			**mMesh;			//����
		PQE_MATERIAL		*mMaterial;		//����
		PQE_TEXTURE			*mTexture;		//����
	};

	class PQE_NODE
	{
	public:
		enum PQE_NODE_TYPE
		{
			PQE_NODE_BONE,
			PQE_NODE_MESH,
			PQE_NODE_MESH_SHAPE,
			PQE_NODE_MESH_ROOT
		};
	public:
		PQE_NODE();
		~PQE_NODE();

	public:
		PQE_NODE_TYPE		mType;			//�ڵ�����
		char				mName[255];		//�ڵ�����
		unsigned int		childNum;		//�ӽڵ�����
		unsigned int		meshNum;		//��������
		unsigned int		shapeNum;		//����������
		unsigned int        mMatrixIndex;	//��������
		unsigned int		shapeVertexNum;	//���������ж���
		unsigned int		*mMeshIndex;	//����
		unsigned int		*mShapeIndex;	//������
		PQE_NODE			*mParent;		//���ڵ�
		PQE_NODE			*mChild;		//�ӽڵ�
		AABB				*aabb;			//��Χ��
	};

	class PQE_MATRIX
	{
	public:
		PQE_MATRIX();
		~PQE_MATRIX();

	public:
		glm::mat4			mSelf;			//�ڵ��ʼ����
		glm::mat4			mFinsh;			//�ڵ���Ծ���
		glm::mat4			mOffset;		//�ڵ�ƫ�ƾ���
	};

	

	class PQE_MESH
	{
	public:
		enum PQE_MESH_TYPE
		{
			PQE_MESH_ORDINARY,
			PQE_MESH_SHAPE,
			PQE_MESH_SHAPE_INDEX
		};
	public:
		PQE_MESH();
		~PQE_MESH();

	public:
		PQE_MESH_TYPE		mType;			//��������
		char				mName[255];		//����
		int					*mShapeVertexIndex;
		unsigned int		vertexNum;		//��������
		unsigned int		faceNum;		//������
		unsigned int		boneNum;		//��������
		unsigned int		mMaterilIndex;	//��������
		unsigned int        mShapeWeight;	//�α�Ȩ��
		unsigned int		*mFace;			//��
		glm::vec3			*mPosition;		//����
		glm::vec3			*mNormal;		//����
		glm::vec2			*mCoord;		//��������
		glm::vec4			*mColor;		//������ɫ
		glm::int4			*mBoneIndex;	//��������
		glm::vec4			*mBoneWeight;	//Ȩ��
		AABB				*aabb;			//aabb��Χ��
	};
	

	class PQE_MATERIAL
	{
	public:
		PQE_MATERIAL();
		~PQE_MATERIAL();

	public:
		unsigned int		materialNum;	//��������
		unsigned int		textureNum;	//��������
		unsigned int		*mTextureIndex;//��������
		PQE_MATERIAL		*mMaterial;	//����
	};
	
	class PQE_TEXTURE
	{
	public:
		enum PQE_TEXTURE_TYPE
		{

		};
	public:
		PQE_TEXTURE();
		PQE_TEXTURE(PQE_TEXTURE_TYPE type, std::string path);
		~PQE_TEXTURE();

	public:
		unsigned int		mId;			//����id
		PQE_TEXTURE_TYPE	mType;			//��������
		char				mPath[255];		//����·��
	};


	class PQEModel
	{
	public:
		PQEModel();
		PQEModel(std::string path);
		~PQEModel();

		void LoadNode(const aiScene *scene);		//��ȡ�ڵ�
		void LoadMesh(const aiScene *scene);		//��ȡ����
		void LoadMaterial(const aiScene *scene);	//��ȡ����
		void LoadShape(std::string path, std::vector<PQE_MESH*> &shape);							//��ȡ���ζ���

		void LoadNodeChild(std::vector<PQE_MATRIX> &vec, aiNode *node, PQE_NODE *pNode, PQE_NODE *pNodeParent, unsigned int &index);

		void LoadMaterialTexture(aiMaterial *material, PQE_MATERIAL *pqematerial, std::vector<PQE_TEXTURE> &texture, unsigned int materialIndex);
		void LoadMaterialTextureChild(aiMaterial *material, PQE_MATERIAL *pqematerial,aiTextureType type, std::vector<PQE_TEXTURE> &path, std::vector<unsigned int> &textureIndex, unsigned int materialIndex);
		bool checkTextureRepeat(PQE_TEXTURE &tex,std::string path);
	
		void GenSpesicalID();
		void GenTextureID();
		std::vector<glm::vec3> GenShapeGpuID();
		void GenShapeGpuData(std::vector<glm::vec3>& pos, PQE_NODE* node, unsigned int& shapeGpuIndex);
		virtual void Render(shader *mshader = NULL);
		inline void RenderChild(PQE_NODE *node, shader *mshader);

		void SetMatrix(PQE_MATRIX *matrix,glm::mat4 *mat);
		void SetMatrix(PQE_NODE *node,glm::mat4 *mat);
		void SetMatrix(std::string name, glm::mat4 *mat);
		void SetBoneSSAOId(unsigned int id);
		void SetShapeSSAOId(unsigned int id);

		void ComputeBoneMatrix(PQE_NODE *node, glm::mat4 parent, glm::mat4 *data);

		PQE_NODE *FindNode(std::string name);
		PQE_MATRIX *FindMatrix(std::string name);
		inline PQE_NODE *FindNodeChild(PQE_NODE *node,std::string name);
		inline PQE_MATRIX *FindMatrixChild(PQE_NODE *node,std::string name);

		inline void InitFbxSdk(FbxManager *&pManager, FbxScene*&pScene);//��ʼ��fbx sdk
		void LoadFbxNode(FbxNode* pNode, std::vector<PQE_MESH*> &shape);
		inline void LoadFbxMesh(FbxNode* pNode, std::vector<PQE_MESH*> &shape);
		inline void LoadFbxShape(FbxMesh* pMesh, PQE_NODE *pqe_node, std::vector<PQE_MESH*> &shape);
		inline void LoadFbxShapeVertexIndex(PQE_NODE *pqe_node, std::vector<PQE_MESH*> &shape, std::vector<glm::vec3> &vertex);

		PQE_MODEL *GetModel();
	private:
		PQE_MODEL *mModel;
		std::string mModelPath;
		std::map<std::string, PQE_NODE*> mMatrixName;
		unsigned int *mesh_vao;
		unsigned int *mesh_ebo;
		unsigned int *mesh_vbo_pos;
		unsigned int *mesh_vbo_nor;
		unsigned int *mesh_vbo_coord;
		unsigned int *bone_ssao;
		unsigned int *shape_ssao;
		unsigned int* shape_vbo;
		unsigned int *bone_weight_vbo;
		unsigned int *bone_index_vbo;
	};
}

