#ifndef _Entity2D_H_
#define _Entity2D_H_

#include "Entity.h"
#include "Defines.h"
#include "renderer.h"
//#include <D3dx8math.H>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace zak {


/**
 *  Clase que contiene las propiedades comunes a todas las entidades 2D.
 *	@author Juan Pablo "McKrackeN" Bettini
 */
class ZAKENGINE_API Entity2D : public ENTITY
{
	public:
		enum CollisionType {
			eCollisionBBox=1,
			eCollisionCircle=2
		};


	protected:
		CollisionType _collisionType;
		float _collisionRadius;


		float _fWidth;
		float _fHeight;
		float _fPosX;
		float _fPosY;
		float _fPreviousPosX;
		float _fPreviousPosY;
		float _fAngleZ;
		float _scale;
		float _scaleX;
		float _scaleY;
		float _pivotPosX;
		float _pivotPosY;

		int   _iCollisionGroup;
		float _fCollisionRelPosX;
		float _fCollisionRelPosY;
		float _fCollisionPosX;
		float _fCollisionPosY;
		float _fCollisionSizeX;
		float _fCollisionSizeY;

		bool  _bMoving;
		bool  _rotating;
		bool  _bCheckCollision;
		float _fMovingSpeed;
		float _fMovingDegrees;
		float _rotationSpeed;

		int	_flipH;
		int	_flipV;

		bool  _bCollisionVisible;
		ColorVertex _VertexColor[5];

	public:
		/**
		 *  Fija el radio del �rea de la colisi�n por c�rculos
		 *	@param radius Radio de la colisi�n por c�rculos
		 */
		void SetCollisionRadius(float radius) {
			_collisionRadius = radius;
		}

		/**
		 *  Devuelve el radio del �rea de la colisi�n por c�rculos
		 *	@return Devuelve el radio
		 */
		float GetCollisionRadius() {
			return _collisionRadius;
		}

		/**
		 *  Fija el grupo de colisi�n al cual pertenece
		 *	@param iColGroup Grupo al de colisi�n al cual pertence
		 */
		void SetCollisionGroup(int iColGroup){
			_iCollisionGroup=iColGroup;
		}
		
		/**
		 *  Devuelve el grupo de colisi�n al cual pertenece
		 *	@return Devuelve el grupo al de colisi�n al cual pertence
		 */
		int GetCollsionGroup(void){
			return _iCollisionGroup;
		}
		
		/**
		 *  Fija un booleano que indica si la entidad chequear� colisi�n o no
		 *	@param bCheckCollision Booleano que indica si la entidad chequear� colisi�n o no
		 */
		void SetCheckCollision(bool bCheckCollision){
			_bCheckCollision=bCheckCollision;
		}

		/**
		 *  Devuelve un booleano que indica si la entidad chequear� colisi�n o no
		 *	@return Booleano que indica si la entidad chequear� colisi�n o no
		 */
		bool GetCheckCollision(){
			return _bCheckCollision;
		}

		/**
		 *  Fija si la entidad se encuentra rotando o no. 
		 *	En el caso de activar �sta propiedad, al llamar al m�todo Update, la entidad rotar� 
		 *	seg�n el par�metro indicado por el m�todo SetRotationSpeed.
		 *	@see SetRotationSpeed()
		 *	@see Update()
		 *	@param rotating booleano que indica si estar� rotando o no
		 */
		void SetRotating(bool rotating){
			_rotating=rotating;
		}

		/**
		 *  Devuelve si la entidad se encuentra rotando o no. 
		 *	@see SetRotating()
		 *	@return Booleano que indica si la rotaci�n est� activada o no
		 */
		bool GetRotating(){
			return _rotating;
		}

		/**
		 *  Fija si la entidad se encuentra movi�ndose o no. 
		 *	En el caso de activar �sta propiedad, al llamar al m�todo Update, la entidad se mover�
		 *	seg�n los par�metros indicados por los m�todo SetSpeed (velocidad) y SetMovDirection 
		 *	(direcci�n de movimiento).
		 *	@see SetSpeed()
		 *	@see SetMovDirection()
		 *	@see Update()
		 *	@param bMoving booleano que indica si estar� rotando o no
		 */
		void SetMoving(bool bMoving){
			_bMoving=bMoving;
		}

		/**
		 *  Devuelve si la entidad se est� moviendo o no. 
		 *	@see SetMoving()
		 *	@return Booleano que indica si el movimiento est� activado o no
		 */
		bool GetMoving(){
			return _bMoving;
		}
		
		/**
		 *  Fija la velocidad de rotaci�n.
		 *	@see SetRotating()
		 *	@see Update()
		 *	@param speed n�mero decimal que indica la velocidad a la que rotar� la entidad
		 */
		void SetRotationSpeed(float speed){
			_rotationSpeed=speed;
		}
		
		/**
		 *  Devuelve la velocidad de rotaci�n fijada por SetRotationSpeed.
		 *	@see SetRotationSpeed()
		 *	@see SetRotating()
		 *	@see Update()
		 *	@return N�mero decimal que indica la velocidad a la que rotar� la entidad
		 */
		float GetRotationSpeed(){
			return _rotationSpeed;
		}

		/**
		 *  Fija la velocidad de traslaci�n de la entidad.
		 *	@see SetMoving()
		 *	@see Update()
		 *	@param speed n�mero decimal que indica la velocidad a la que se trasladar� la entidad
		 */
		void SetSpeed(float speed){
			_fMovingSpeed=speed;
		}
		
		/**
		 *  Devuelve la velocidad de traslaci�n de la entidad.
		 *	@see SetSpeed()
		 *	@see SetMoving()
		 *	@see Update()
		 *	@return N�mero decimal que indica la velocidad a la que se trasladar� la entidad
		 */
		float GetSpeed(){
			return _fMovingSpeed;
		}
		
		/**
		 *  Fija la direcci�n en la que se trasladar� la entidad
		 *	@see SetSpeed()
		 *	@see SetMoving()
		 *	@see Update()
		 *	@param direction n�mero decimal que indica el �ngulo de direcci�n
		 */
		void SetMovDirection(float direction){
			_fMovingDegrees=direction;
		}
		
		/**
		 *  Devuelve la direcci�n en la que se trasladar� la entidad
		 *	@see SetSpeed()
		 *	@see SetMoving()
		 *	@see Update()
		 *	@return N�mero decimal que indica el �ngulo de direcci�n
		 */
		float GetMovDirection(){
			return _fMovingDegrees;
		}
		
		/**
		 *  Fija la posici�n en el eje X
		 *	@param posX n�mero decimal que indica la posici�n en el eje X
		 */
		void SetPosX(float posX) {
			_fPreviousPosX = _fPosX;
			_fPosX = posX;
			_fCollisionPosX=_fCollisionRelPosX+_fPosX;
		}

		/**
		 *  Fija la posici�n en el eje Y
		 *	@param posY n�mero decimal que indica la posici�n en el eje Y
		 */
		void SetPosY(float posY) {
			_fPreviousPosY = _fPosY;
			_fPosY = posY;
			_fCollisionPosY=_fCollisionRelPosY+_fPosY;
		}
	
		/**
		 *  Fija la posici�n en ambos ejes cartesianos
		 *	@param fPosx n�mero decimal que indica la posici�n en el eje X
		 *	@param fPosy n�mero decimal que indica la posici�n en el eje Y
		 */
		void SetPos(float fPosx, float fPosy) {
			_fPreviousPosX = _fPosX;
			_fPreviousPosY = _fPosY;
			_fPosX = fPosx;
			_fPosY = fPosy;
			_fCollisionPosX=_fCollisionRelPosX+_fPosX;
			_fCollisionPosY=_fCollisionRelPosY+_fPosY;
		}

		/**
		 *  Devuelve la posici�n en ambos ejes cartesianos
		 *	@param fPosx n�mero decimal que indica la posici�n en el eje X
		 *	@param fPosy n�mero decimal que indica la posici�n en el eje Y
		 */
		void GetPos(float &fPosx, float &fPosy) {
			fPosx = _fPosX;
			fPosy = _fPosY;
		}

		/**
		 *  Devuelve la posici�n en el eje X
		 *	@return N�mero decimal que indica la posici�n en el eje X
		 */
		float GetPosX() {
			return _fPosX;
		}

		/**
		 *  Devuelve la posici�n en el eje Y
		 *	@return N�mero decimal que indica la posici�n en el eje Y
		 */
		float GetPosY() {
			return _fPosY;
		}
	
		/**
		 *  Fija la posici�n de la entidad a su posici�n en la iteraci�n anterior
		 */
		void SetToPreviousPosition() {
			_fPosX = _fPreviousPosX;
			_fPosY = _fPreviousPosY;
		}

		/**
		*	Devuelve la posici�n anterior en ambos ejes cartesianos
		*	@param fPosx n�mero decimal que indica la posici�n en el eje X
		*	@param fPosy n�mero decimal que indica la posici�n en el eje Y
		*/
		void GetPreviousPos(float &fPosx, float &fPosy) {
			fPosx = _fPreviousPosX;
			fPosy = _fPreviousPosY;
		}

		/**
		*	Devuelve la posici�n anterior en el eje X
		*	@return Retorna la posici�n anterior en el eje X
		*/
		float GetPreviousPosX() {
			return _fPreviousPosX;
		}

		/**
		*	Devuelve la posici�n anterior en el eje Y
		*	@return Retorna la posici�n anterior en el eje Y
		*/
		float GetPreviousPosY() {
			return _fPreviousPosY;
		}

		/**
		 *  Devuelve el tipo de colisi�n de la entidad
		 *	@return Devuelve un tipo enumerador que indica el tipo de colisi�n de la entidad
		 */
		CollisionType GetCollisionType() {
			return _collisionType;
		}

		/**
		 *  Fija el tipo de colisi�n de la entidad
		 *	@param  collisionType Tipo enumerador que indica el tipo de colisi�n de la entidad
		 */
		void SetCollisionType(CollisionType collisionType) {
			_collisionType = collisionType;
		}

		/**
		 *  Fija la posici�n relativa a la entidad del �rea de colisi�n
		 *	@param fPosx posici�n en el eje X del �rea de colisi�n
		 *	@param fPosy posici�n en el eje Y del �rea de colisi�n
		 */
		void SetCollisionPos(float fPosx, float fPosy) {
			_fCollisionRelPosX = fPosx;
			_fCollisionRelPosY = fPosy;
			_fCollisionPosX = fPosx;
			_fCollisionPosY = fPosy;
			_fCollisionPosX+=_fPosX;
			_fCollisionPosY+=_fPosY;
		}

		/**
		 *  Devuelve la posici�n relativa a la entidad del �rea de colisi�n
		 *	@param fPosx posici�n en el eje X del �rea de colisi�n
		 *	@param fPosy posici�n en el eje Y del �rea de colisi�n
		 */
		void GetCollisionPos(float &fPosx, float &fPosy) {
			fPosx = _fCollisionPosX;
			fPosy = _fCollisionPosY;
		}

		/**
		 *  Fija el tama�o del �rea de colisi�n 
		 *	@param fSizeX ancho del �rea de colisi�n
		 *	@param fSizeY alto del �rea de colisi�n
		 */
		void SetCollisionSize(float fSizeX, float fSizeY) {
			_fCollisionSizeX = fSizeX;
			_fCollisionSizeY = fSizeY;
		}

		/**
		 *  Devuelve el tama�o del �rea de colisi�n 
		 *	@param fSizeX ancho del �rea de colisi�n
		 *	@param fSizeY alto del �rea de colisi�n
		 */
		void GetCollisionSize(float &fSizeX, float &fSizeY) {
			fSizeX = _fCollisionSizeX;
			fSizeY = _fCollisionSizeY;
		}
		
		/**
		 *  Fija la visibilidad del �rea de colisi�n
		 *	@see DrawCollision()
		 *	@param bCollisionVisible booleano que indica si el �rea de colisi�n ser� visible o no
		 */
		void SetCollisionVisible(bool bCollisionVisible) {
			_bCollisionVisible = bCollisionVisible;
		}

		/**
		 *  Fija la rotaci�n de la entidad
		 *	@param fAngleZ n�mero decimal que indica el �ngulo en grados que se rotar� la entidad
		 */
		void SetAngleZ (float fAngleZ) {
			_fAngleZ = D3DXToRadian(fAngleZ);
		}

		/**
		 *  Devuelve la rotaci�n de la entidad
		 *	@return N�mero decimal que indica el �ngulo en grados que se rotar� la entidad
		 */
		float  GetAngleZ () {
			return D3DXToDegree(_fAngleZ);
		}

		/**
		 *  Fija el tama�o de la entidad
		 *	@param w ancho de la entidad
		 *	@param h alto de la entidad
		 */
		void SetDim(float w, float h) 
		{
			_fWidth = w;
			_fHeight = h;
		};

		/**
		 *  Devuelve el tama�o de la entidad
		 *	@param w ancho de la entidad
		 *	@param h alto de la entidad
		 */
		void GetDim(float &w, float &h) 
		{
			w = _fWidth;
			h = _fHeight;
		};
		
		/**
		 *  Devuelve el ancho de la entidad
		 *	@return Ancho de la entidad
		 */
		float GetWidth() 
		{
			return _fWidth;
		};

		/**
		 *  Devuelve el alto de la entidad
		 *	@return Alto de la entidad
		 */
		float GetHeight() 
		{
			return _fHeight;
		};

		/**
		 *  Fija la escala de la entidad. Su valor por defecto es 1.0f en ambos ejes.
		 *	@param x escala en el eje X de la entidad
		 *	@param y escala en el eje Y de la entidad
		 */
		void SetScale(float x, float y) {
			_scaleX = x;
			_scaleY = y;
			_scale = x;
		}

		/**
		 *  Devuelve la escala.
		 *	@return escala de la entidad
		 */
		float GetScale() {
			return _scale;
		}

		/**
		 *  Fija la escala de la entidad. Su valor por defecto es 1.0f.
		 *	@return escala de la entidad
		 */
		void SetScale(float scale) {
			_scale = scale;
			_scaleX = scale;
			_scaleY = scale;
		}

		/**
		 *  Fija la escala de la entidad en el eje X. Su valor por defecto es 1.0f.
		 *	@param x escala de la entidad en el eje X.
		 */
		void SetScaleX(float x) {
			_scaleX = x;
			_scale = x;
		}

		/**
		 *  Fija la escala de la entidad en el eje Y. Su valor por defecto es 1.0f.
		 *	@param y escala de la entidad en el eje Y.
		 */
		void SetScaleY(float y) {
			_scaleY = y;
			_scale = y;
		}

		/**
		 *  Devuelve la escala de la entidad en el eje X. 
		 *	@return Escala de la entidad en el eje X.
		 */
		float GetScaleX() {
			return _scaleX;
		}

		/**
		 *  Devuelve la escala de la entidad en el eje Y. Su valor por defecto es 1.0f.
		 *	@return Escala de la entidad en el eje Y.
		 */
		float GetScaleY() {
			return _scaleY;
		}

		/**
		 *  Invierte la entidad horizontalmente
		 */
		void FlipHorizontal() {
			_flipH *= -1;
		}

		/**
		 *  Invierte la entidad verticalmente
		 */
		void FlipVertical() {
			_flipV *= -1;
		}

		/**
		*  Posiciona el p�vot
		*  @param x posici�n en el eje X
		*  @param y posici�n en el eje Y
		*/
		void SetPivotPos(float x, float y) {
			_pivotPosX = x;
			_pivotPosY = y;
		}

		/**
		*  Posiciona el p�vot en el eje X
		*  @param x posici�n en el eje X
		*/
		void SetPivotPosX(float x) {
			_pivotPosX = x;
		}

		/**
		*  Posiciona el p�vot en el eje Y
		*  @param y posici�n en el eje Y
		*/
		void SetPivotPosY(float y) {
			_pivotPosY = y;
		}

		/**
		*  Devuelve la posici�n en el eje X
		*  @return Posici�n del p�vot en el eje X
		*/
		float GetPivotPosX() {
			return _pivotPosX;
		}

		/**
		*  Devuelve la posici�n en el eje Y
		*  @return Posici�n del p�vot en el eje Y
		*/
		float GetPivotPosY() {
			return _pivotPosY;
		}

		/**
		*  Setea la posici�n de la entidad relativa al centro dadas una direcci�n y una distancia
		*  @param fAngle �ngulo que define la direcci�n
		*  @param fDistance distancia del centro
		*/
		void SetRelativePos(float fAngle, float fDistance)
		{
			_fPosX +=	fDistance * 
						(float) cos(D3DXToRadian(fAngle));

			_fPosY +=	fDistance * 
						(float) sin(D3DXToRadian(fAngle));

			_fCollisionPosX=_fCollisionRelPosX+_fPosX;
			_fCollisionPosY=_fCollisionRelPosY+_fPosY;
		}

		/**
		*  Actualiza la entidad
		*  @param fTimeBetweenFrames tiempo transcurridos en cada iteraci�n
		*/
		virtual void Update(float fTimeBetweenFrames) {
			_fPreviousPosX = _fPosX;
			_fPreviousPosY = _fPosY;

			if (_bMoving) {
				_fPosX +=	fTimeBetweenFrames * 
							_fMovingSpeed * 
							(float) sin(D3DXToRadian(_fMovingDegrees));

				_fPosY +=	fTimeBetweenFrames *
							_fMovingSpeed * 
							(float) cos(D3DXToRadian(_fMovingDegrees));

				_fCollisionPosX=_fPosX + _fCollisionRelPosX * cos(D3DXToRadian(_fMovingDegrees));
				_fCollisionPosY=_fPosY + _fCollisionRelPosY * sin(D3DXToRadian(_fMovingDegrees));
			}

			if (_rotating) {
				_fAngleZ += _rotationSpeed*fTimeBetweenFrames;
			}
		}

		/**
		*  Dibuja la entidad
		*/
		virtual void Draw()
		{
			// se modifica la matriz de translacion
			g_renderer.SetMatrixMode(ZAK_WORLD_MATRIX);
			g_renderer.LoadIdentity();

			g_renderer.Translate (_fPosX, _fPosY, 1.0f);
//			g_renderer.Translate (_fCollisionPosX, _fCollisionPosY, 1.0f);

			g_renderer.RotationZ(_fAngleZ);
			g_renderer.Translate (_pivotPosX, _pivotPosY, 1.0f);
			g_renderer.Scale(_scaleX, _scaleY);
		}

		/**
		*  Dibuja el �rea de colisi�n
		*/
		void DrawCollision()
		{
			if (_bCollisionVisible) {
				// se modifica la matriz de translacion
				g_renderer.SetMatrixMode(ZAK_WORLD_MATRIX);
				g_renderer.LoadIdentity();

				g_renderer.Translate (_fCollisionPosX, _fCollisionPosY, 1.0f);

				g_renderer.BindTexture(-1);

				_VertexColor[0].SetVal(-_fCollisionSizeX/2*_scaleX, -_fCollisionSizeY/2*_scaleY, 1.0f,0xffffffff);
				_VertexColor[1].SetVal(-_fCollisionSizeX/2*_scaleX,  _fCollisionSizeY/2*_scaleY, 1.0f,0xffffffff);
				_VertexColor[2].SetVal( _fCollisionSizeX/2*_scaleX,  _fCollisionSizeY/2*_scaleY, 1.0f,0xffffffff);
				_VertexColor[3].SetVal( _fCollisionSizeX/2*_scaleX, -_fCollisionSizeY/2*_scaleY, 1.0f,0xffffffff);
				_VertexColor[4].SetVal(-_fCollisionSizeX/2*_scaleX, -_fCollisionSizeY/2*_scaleY, 1.0f,0xffffffff);


				g_renderer.Draw(_VertexColor, ZAK_PRI_LINESTRIP,5);
			}
		}

		/**
		*  Devuelve si la entidad est� colisionando con otra
		*  @param pEntity entidad contra la que se chequear� la colisi�n
		*  @return devuelve verdadero si hubo colisi�n y falso en caso contrario
		*/
		virtual bool IsColliding(Entity2D *pEntity) 
		{
			if (_bCheckCollision && pEntity->GetCheckCollision()) {
				float X1, Y1;
				float W, H;
				float R;

				switch (_collisionType) {
					case eCollisionBBox:

						pEntity->GetCollisionPos(X1,Y1);
						pEntity->GetCollisionSize(W, H);

						W *= pEntity->GetScaleX();
						H *= pEntity->GetScaleY();

						if (((_fCollisionPosX-(_fCollisionSizeX/2*_scaleX) < X1-(W/2) && X1-(W/2) < _fCollisionPosX + _fCollisionSizeX/2*_scaleX) ||
							 (X1-(W/2) < _fCollisionPosX-(_fCollisionSizeX/2*_scaleX) && _fCollisionPosX-(_fCollisionSizeX/2*_scaleX) < X1+W/2)) &&
							((_fCollisionPosY-(_fCollisionSizeY/2*_scaleY) < Y1-(H/2) && Y1-(H/2) < _fCollisionPosY+_fCollisionSizeY/2*_scaleY) ||
							 (Y1-(H/2) < _fCollisionPosY-(_fCollisionSizeY/2*_scaleY) && _fCollisionPosY-(_fCollisionSizeY/2*_scaleY) < Y1 + H/2))) {

							return true;
						}
						break;
					case eCollisionCircle:
					default:

						pEntity->GetCollisionPos(X1,Y1);
						R = pEntity->GetCollisionRadius();

						R *= pEntity->GetScale();

						if ((X1- _fCollisionPosX)*(X1- _fCollisionPosX)+(Y1-_fCollisionPosY)*(Y1-_fCollisionPosY) < (R+_collisionRadius*_scale)*(R+_collisionRadius*_scale)) {
							return true;
						}

						break;
				}
			}
			return false;
		}

		/**
		*  M�todo virtual que debemos invocar en caso de haber colisi�n
		*  @param pEntity entidad contra la que se ha colisionado
		*/
		virtual void OnCollide(Entity2D *pEntity) 
		{
		}

		/**
		*  Constructor
		*/
		Entity2D()
		{
			_iCollisionGroup=0;
			_fPosX = 0;
			_fPosY = 0;
			_fPreviousPosX = 0;
			_fPreviousPosY = 0;
			_fCollisionRelPosX = 0;
			_fCollisionRelPosY = 0;
			_fCollisionPosX = 0;
			_fCollisionPosY = 0;
			_fCollisionSizeX = 0;
			_fCollisionSizeY = 0;
			_fWidth = 0;
			_fHeight = 0;
			_fAngleZ = 0;
			_bCheckCollision = false;
			_bMoving = false;
			_fMovingSpeed	 = 0;
			_fMovingDegrees = 0;
			_bCollisionVisible = false;
			_rotationSpeed = 0;
			_rotating = false;
			_scale = 1.0f;
			_scaleX = 1.0f;
			_scaleY = 1.0f;
			_collisionType = eCollisionCircle;
			_flipH = 1;
			_flipV = 1;
			_pivotPosX = 0.0f;
			_pivotPosY = 0.0f;
		}

		/**
		*  Destructor
		*/
		virtual ~Entity2D(){}

};

}

#endif // _Entity2D_H_
