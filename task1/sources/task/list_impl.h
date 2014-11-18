/**
* @file: task/list_impl.h
* Solution implementation of the programming task 1
*/

namespace Task
{
// ---- DList::Unit class implementation ----

    template <class T> DList<T>::Unit::Unit()
	{
		nextUnit = prevUnit = NULL;
	}

    template <class T> typename DList<T>::Unit* DList<T>::Unit::next()
    {
		if (this == NULL)
		{
			return NULL;
		}
		else
		{
			return this->nextUnit;
		}
    }

    template <class T> void DList<T>::Unit::setNext(typename DList<T>::Unit *u)
    {
		if (this == NULL)
		{

		}
		else
		{
			this->nextUnit = u;
		}
    }

    template <class T> typename DList<T>::Unit* DList<T>::Unit::prev()
    {
		if (this == NULL){
			return NULL;
		}
		else
		{
			return this->prevUnit;
		}
	}

	template <class T> void DList<T>::Unit::setPrev(typename DList<T>::Unit *u)
	{
		if (this == NULL)
		{

		}
		else
		{
			this->prevUnit = u;
		}
	}

    template <class T> T& DList<T>::Unit::val()
    {
        return value;
    }

// ---- End of DList::Unit class implementation ----

// ---- DList template class implementation ----


	template <class T> DList<T>::DList()
	{
		head = tail = NULL;
		numberOfUnits=0;
	}

    template <class T> DList<T>::~DList()          
    {
        clear();
    }

    template <class T> void DList<T>::push_front (const T& val)
    {
		Unit* newUnit = new Unit;
		newUnit->val() = val;
		if (numberOfUnits == 0)
		{
			head = tail = newUnit;
			numberOfUnits++;
		}
		else
		{
			head->setPrev(newUnit);
			newUnit->setNext(head);
			head = newUnit;
			numberOfUnits++;
		}
    }

    template <class T> void DList<T>::pop_front()
    {
       if (numberOfUnits == 0)
		{

		}
        else if(numberOfUnits == 1)
        {
            delete head;
            head=NULL;
            tail=NULL;
            numberOfUnits=0;
		}
		else{
			head = head->next();
			delete head->prev();
			head->setPrev(NULL);
			numberOfUnits--;
		}
    }

    template <class T> void DList<T>::push_back (const T& val)
    {
		Unit* newUnit = new Unit;
		newUnit->val() = val;
        if(numberOfUnits == 0)
        {
            head=newUnit;
            tail=newUnit;
            numberOfUnits++;
		}
		else
		{
			tail->setNext(newUnit);
			newUnit->setPrev(tail);
			tail = newUnit;
			numberOfUnits++;
		}
    }

    template <class T> void DList<T>::pop_back()
    {
		if (numberOfUnits == 0)
		{

		}
		else if (numberOfUnits == )
        {
            delete tail;
            head=NULL;
            head=NULL;
			numberOfUnits=0;
		}
		else
		{
			tail = tail->prev();
			delete tail->next();
			tail->setNext(NULL);
			numberOfUnits--;
		}
    }
	
    template <class T> typename DList<T>::Unit* DList<T>::insert (typename DList<T>::Unit *u, const T& val)
    {
     
		Unit* newUnit = new Unit;
		newUnit->val() = val;
        newUnit->setPrev(u->prev());
        newUnit->setNext(u);

        if( u->prev() == NULL)      
        {
            head=newUnit;
            u->setPrev(newUnit);
            numberOfUnits++;
        }
		else
		{
			(u->prev())->setNext(newUnit);
			u->setPrev(newUnit);
			numberOfUnits++;
		}

        return newUnit;
    }
	
    template <class T> typename DList<T>::Unit* DList<T>::first()
    {
        return head;
    }

    template <class T> typename DList<T>::Unit* DList<T>::last()
    {
		return tail;
    }

    template <class T> typename DList<T>::Unit* DList<T>::erase (typename DList<T>::Unit *u)
    {
       
		if (u == NULL)
		{
			return NULL;
		}
		else if (numberOfUnits == 0)
		{
			return NULL;
		}
        else if(numberOfUnits==1) 
        {
            head=NULL;
            tail=NULL;
            numberOfUnits--;
            delete u;
            return NULL;
        }
		else if(u==head && numberOfUnits>1) 
        {
            head=head->next();
            head->setPrev(NULL);
            numberOfUnits--;
            delete u;
            return head;
        }
		else if(u==tail && numberOfUnits>1)
        {
            tail=tail->prev();
            tail->setNext(NULL);
            numberOfUnits--;
            delete u;
            return NULL;
		}
		else
		{
			Unit *returnUnit = new Unit;
			returnUnit = u->next();
			(u->prev())->setNext(u->next());
			(u->next())->setPrev(u->prev());
			numberOfUnits--;
			delete u;
			return returnUnit;
		}
        
    }
	
    template <class T> void DList<T>::clear()
    {
		if (numberOfUnits == 0)
		{

		}
		else if(numberOfUnits==1)
        {
            delete head;
            head=NULL;
            tail=NULL;
            numberOfUnits=0;
		}
		else
		{

			Unit* tmp = head;

			do{
				tmp = tmp->next();
				delete tmp->prev();
			} while (tmp != tail);

			delete tail;

			head = NULL;
			tail = NULL;
			numberOfUnits = 0;
		}
		}

	template <class T> bool DList<T>::empty()
    {
		if (numberOfUnits == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	template <class T> unsigned DList<T>::size()
    {
        return numberOfUnits;
    }

    template <class T> void DList<T>::reverse()
    {

		Unit* buff;
		Unit* buff1;
		T tmp;
		int count = 0;

		tmp = head->val();
		head->val() = tail->val();
		tail->val()=tmp;
		buff = head->next();
		buff1 = tail->prev();

		for (count; count < numberOfUnits/ 2 - 1; count++)
		{
			tmp = buff->val();
			buff->val() = buff1->val();
			buff1->val()=tmp;
			buff = buff->next();
			buff1 = buff1->prev();
		}

    }

// ---- End of DList template class implementation ----
};