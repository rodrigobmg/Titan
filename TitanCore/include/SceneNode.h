#ifndef _TITAN_SCENENODE_HH
#define _TITAN_SCENENODE_HH

#include "TitanPrerequisites.h"
#include "TitanCommon.h"
#include "TitanMatrix4.h"
#include "TitanIteratorWrapper.h"

namespace Titan
{
	class _DllExport SceneNode : public GeneralAlloc
	{
	public:
		typedef HashMap<String, SceneNode*>	SceneNodeMap;
		typedef HashMap<String, SceneObject*>	SceneObjectMap;
		typedef MapIterator<SceneObjectMap> ObjectIterator;
		typedef ConstMapIterator<SceneObjectMap> ConstObjectIterator;
		typedef MapIterator<SceneNodeMap> ChildIterator;
		typedef ConstMapIterator<SceneNodeMap> ConstChildIterator;
	public:
		SceneNode(const String& name);
		
		~SceneNode();

		void	attachObject(SceneObject* object);

		void	detachObject(const String& objectName);

		void    detachObject(SceneObject* object);

		SceneNode*	createChild(const String& name, const Vector3& v = Vector3::ZERO,
			const Quaternion& q = Quaternion::IDENTITY);

		SceneNode*	createChild(const Vector3& v = Vector3::ZERO,
			const Quaternion& q = Quaternion::IDENTITY);

		void		addChild(SceneNode* child);

		void		removeChild(const String& name);

		void		removeChild(SceneNode* child);

		void		scale(float x, float y, float z);

		void		scale(const Vector3& vec);

		const Vector3& getScale() const { return mScale;}

		void		rotate(const Quaternion& q);

		void		rotate(const Vector3& axis, const Radian& angle);

		const Quaternion& getOrientation() const { return mQuaternion; }

		void		translate(float x, float y, float z);

		void		translate(const Vector3& pos);

		const Vector3&	getPosition() const { return mPosition; }

		const Vector3&	_getDerivedScale() const { return mDerivedScale; }

		const Quaternion& _getDerivedOrientation() const { return mDerivedQuaternion; }

		const Vector3&	  _getDerivedPosition() const { return mDerivedPosition; }

		const Matrix4&	 _getTransformMatrix();

		void		notifyUpdate();

		void		_update();

		void		_updateFromParent();

		void		_setParent(SceneNode* parent);

		SceneNode*	getParent() const { return mParent; }

		const String& getName() const { return mName; }

		virtual ObjectIterator 	getAttachedObjectIterator();

		virtual ConstObjectIterator getAttachedConstObjectIterator();

		virtual ChildIterator 	getChildIterator();

		virtual ConstChildIterator getConstChildIterator();

	protected:
		SceneNode*		mParent;
		String			mName;

		SceneNodeMap	mChildrenMap;
		SceneObjectMap	mSceneObjects;
		

		static	AutoNamer	msAutoNamer;

		Quaternion		mQuaternion;
		Vector3			mScale;
		Vector3			mPosition;

		Quaternion		mDerivedQuaternion;
		Vector3			mDerivedScale;
		Vector3			mDerivedPosition;

		Matrix4			mTransformMat;

		bool			mNeedUpdate;
		bool			mNeedUpdateMat;

	};
}
#endif